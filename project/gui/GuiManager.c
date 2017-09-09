//
// Created by Ido on 9/9/17.
//

#include "GuiManager.h"

GUI_MANAGER *createManager() {
    GUI_MANAGER *manager = (GUI_MANAGER *) malloc(sizeof(GUI_MANAGER));
    if (manager == NULL) return NULL;

    manager->activeWindow = WELCOME_WINDOW;
    manager->genericWindow = createGenericWindow(drawWelcomeWindow);
    return manager;
}

void destroyManager(GUI_MANAGER *manager) {
    if (manager == NULL) return;
    destroyWindow(manager->genericWindow);
    free(manager);
}

MANAGER_EVENT managerEventHandler(GUI_MANAGER *manager, SDL_Event *event) {
    if (manager == NULL || event == NULL) return NULL;

    switch (event->type) {
        case SDL_WINDOWEVENT :
            if (event->window.event == SDL_WINDOWEVENT_CLOSE) return MANAGER_QUIT;
    }
}