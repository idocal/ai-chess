//
// Created by Ido on 9/9/17.
//

#include "GuiManager.h"

GUI_MANAGER *createManager() {
    GUI_MANAGER *manager = (GUI_MANAGER *) malloc(sizeof(GUI_MANAGER));
    if (manager == NULL) return NULL;

    manager->genericWindow = createGenericWindow(drawWelcomeWindow);
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
            SDL_HideWindow(manager->genericWindow->window); // Hide previous screen
            pushNewWindow(stack, response->window);
            manager->genericWindow = response->window;
            SDL_ShowWindow(manager->genericWindow->window); // Show previous screen
        }

        else if (response->status == BACK_WINDOW) {
            popHeadWindow(stack); // Destroys the window (so no need to hide)
            manager->genericWindow = stack->head->window; // Pull stack's head as window since it's the previous screen
            manager->genericWindow->window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, NARROW_WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
            manager->genericWindow->renderer = SDL_CreateRenderer(manager->genericWindow->window, -1, SDL_RENDERER_ACCELERATED);
            reRenderWindow(manager->genericWindow);
        }

        destroyEventResponse(response);
        return MANAGER_NONE;
    }
    return MANAGER_NONE;
}