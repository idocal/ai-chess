//
// Created by Ido on 9/9/17.
//

#include "GuiManager.h"

GUI_MANAGER *createManager(SDL_Window *sdlWindow, SDL_Renderer *renderer) {
    GUI_MANAGER *manager = (GUI_MANAGER *) malloc(sizeof(GUI_MANAGER));
    if (manager == NULL) return NULL;

    manager->genericWindow = createGenericWindow(drawWelcomeWindow, sdlWindow, renderer);
    if (manager->genericWindow == NULL) {
        free(manager);
        return NULL;
    }

    manager->match = createNewChessMatch();
    if (manager->match == NULL) {
        destroyWindow(manager->genericWindow);
        free(manager);
        return NULL;
    }
    initGameBoard(manager->match->game); // Initiate the game board;

    manager->stack = createEmptyWindowsStack();
    if (manager->stack == NULL){
        destroyChessMatch(manager->match);
        destroyWindow(manager->genericWindow);
        free(manager);
        return NULL;
    }

    manager->movesStack = createEmptyStack(UNDO_CAPACITY);
    if (manager->movesStack == NULL){
        destroyWindowsStack(manager->stack);
        destroyChessMatch(manager->match);
        destroyWindow(manager->genericWindow);
        free(manager);
        return NULL;
    }

    pushNewWindow(manager->stack, manager->genericWindow);

    return manager;
}

void destroyManager(GUI_MANAGER *manager) {
    if (manager == NULL) return;
    destroyChessMatch(manager->match);
    destroyWindowsStack(manager->stack);
    destroyStack(manager->movesStack);
    free(manager);
}

MANAGER_EVENT managerEventHandler(GUI_MANAGER *manager, SDL_Event *event) {
    if (manager == NULL || event == NULL) return MANAGER_NONE;
    GENERIC_WINDOW *window = manager->genericWindow;
    CHESS_MATCH *match = manager->match;
    WINDOWS_STACK *stack = manager->stack;
    MOVES_STACK *movesStack = manager->movesStack;

    if (event->type == SDL_WINDOWEVENT) {
        if (event->window.event == SDL_WINDOWEVENT_CLOSE) return MANAGER_QUIT;
    }

    else if (event->type == SDL_MOUSEBUTTONDOWN) {
        EVENT_RESPONSE *response = (EVENT_RESPONSE *)(*window->handleWindowEvent)(window, event, match, movesStack);

        if (response == NULL || response->status == EXIT_WINDOW){
            return MANAGER_QUIT;
        }

        if (response->status == NEW_WINDOW) {
            destroyWindow(manager->genericWindow);
            manager->genericWindow = createWindowFromType(response->windowType, manager);
            if (manager->genericWindow == NULL) return MANAGER_QUIT;
            pushNewWindow(stack, manager->genericWindow);


        } else if (response->status == SAME_WINDOW){ // same window but with different active buttons so need to update stack
            popHeadWindow(stack);
            pushNewWindow(stack, manager->genericWindow); // pushing the current window since action is SAME_WINDOW
        }

        else if (response->status == BACK_WINDOW) {
            popHeadWindow(stack); // Pop window details from stack
            destroyWindow(window); // Destroy the current window (so no need to hide)
            WINDOW_TYPE prevWindowType = stack->head->windowType;
            int windowState = stack->head->windowState;
            GENERIC_WINDOW *nextWindow = NULL;

            if (prevWindowType == WELCOME_WINDOW){
                nextWindow = createGenericWindow(drawWelcomeWindow, window->window, window->renderer);
            } else if (prevWindowType == SETTINGS_MODE_WINDOW){
                nextWindow = createGenericWindow(drawSettingsWindow, window->window, window->renderer);
            } else if (prevWindowType == SETTINGS_DIFFICULTY_WINDOW) {
                nextWindow = createGenericWindow(drawDifficultyWindow, window->window, window->renderer);
                toggleButton(nextWindow->widgets[2], nextWindow->renderer);
                toggleButton(nextWindow->widgets[windowState], nextWindow->renderer);
                reRenderWindow(nextWindow);
                match->level = windowState;
            }

            manager->genericWindow = nextWindow;
        }

        destroyEventResponse(response);
        return MANAGER_NONE;
    }
    return MANAGER_NONE;
}

GENERIC_WINDOW *createWindowFromType(WINDOW_TYPE type, GUI_MANAGER *manager) {
    GENERIC_WINDOW *nextWindow = manager->genericWindow;

    switch (type) {
        case WELCOME_WINDOW :
            nextWindow = createGenericWindow(drawWelcomeWindow, manager->genericWindow->window, manager->genericWindow->renderer);
            break;

        case SETTINGS_MODE_WINDOW :
            nextWindow = createGenericWindow(drawSettingsWindow, manager->genericWindow->window, manager->genericWindow->renderer);
            break;

        case SETTINGS_DIFFICULTY_WINDOW :
            nextWindow = createGenericWindow(drawDifficultyWindow, manager->genericWindow->window, manager->genericWindow->renderer);
            break;

        case SETTINGS_COLOR_WINDOW :
            nextWindow = createGenericWindow(drawColorWindow, manager->genericWindow->window, manager->genericWindow->renderer);
            break;

        case GAME_WINDOW :
            nextWindow = createGenericWindow(drawGameWindow, manager->genericWindow->window, manager->genericWindow->renderer);
            break;

        case LOAD_WINDOW :
            nextWindow = createGenericWindow(drawLoadGameWindow, manager->genericWindow->window, manager->genericWindow->renderer);
            break;

        default :
            return nextWindow;
    }

    return nextWindow;
}