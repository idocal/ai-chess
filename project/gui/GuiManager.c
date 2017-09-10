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

    manager->stack = createEmptyWindowsStack();
    if (manager->stack == NULL){
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
    free(manager);
}

MANAGER_EVENT managerEventHandler(GUI_MANAGER *manager, SDL_Event *event) {
    if (manager == NULL || event == NULL) return MANAGER_NONE;
    GENERIC_WINDOW *window = manager->genericWindow;
    CHESS_MATCH *match = manager->match;
    WINDOWS_STACK *stack = manager->stack;

    if (event->type == SDL_WINDOWEVENT) {
        if (event->window.event == SDL_WINDOWEVENT_CLOSE) return MANAGER_QUIT;
    }

    else if (event->type == SDL_MOUSEBUTTONDOWN) {
        EVENT_RESPONSE *response = (EVENT_RESPONSE *)(*window->handleWindowEvent)(window, event, match);

        if (response == NULL || response->status == EXIT_WINDOW){
            return MANAGER_QUIT;
        }

        if (response->status == NEW_WINDOW){
            destroyWindow(manager->genericWindow);
            pushNewWindow(stack, response->window);
            manager->genericWindow = response->window;


        } else if (response->status == SAME_WINDOW){ // same window but with different active buttons so need to update stack
            popHeadWindow(stack);
            pushNewWindow(stack, response->window);
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