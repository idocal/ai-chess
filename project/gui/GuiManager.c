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
            GENERIC_WINDOW *nextWindow = (*window->handleWindowEvent)(window, event, match);
            if (nextWindow == NULL){
                return MANAGER_QUIT;
            }
            if (manager->genericWindow != nextWindow){
                pushNewWindow(manager->stack, nextWindow);
            }
            manager->genericWindow = nextWindow;
            SDL_ShowWindow(manager->genericWindow->window);
            return MANAGER_NONE;
        }
    return MANAGER_NONE;
}