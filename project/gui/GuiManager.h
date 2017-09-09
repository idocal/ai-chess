//
// Created by Ido on 9/9/17.
//

#include "GenericWindow.h"
#include "WelcomeWindow.h"

#ifndef PROJECT_GUIMANAGER_H
#define PROJECT_GUIMANAGER_H

typedef enum {
    WELCOME_WINDOW,
    GAME_WINDOW,
    LOAD_WINDOW,
    SETTINGS_MODE_WINDOW,
    SETTINGS_DIFFICULTY_WINDOW,
    SETTINGS_COLOR_WINDOW
} ACTIVE_WINDOW;

typedef enum {
    MANAGER_NONE,
    MANAGER_QUIT
} MANAGER_EVENT;

typedef struct guiManager {
    ACTIVE_WINDOW activeWindow;
    GENERIC_WINDOW *genericWindow;
} GUI_MANAGER;

GUI_MANAGER *createManager();
void destroyManager(GUI_MANAGER *manager);

MANAGER_EVENT managerEventHandler(GUI_MANAGER *manager, SDL_Event *event);

#endif //PROJECT_GUIMANAGER_H
