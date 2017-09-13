//
// Created by Ido on 9/9/17.
//

#include "WelcomeWindow.h"
#include "SettingsWindow.h"
#include "DifficultyWindow.h"
#include "ColorWindow.h"
#include "GameWindow.h"
#include "LoadGamesWindow.h"
#include "WindowsStack.h"

#ifndef PROJECT_GUIMANAGER_H
#define PROJECT_GUIMANAGER_H

typedef enum {
    MANAGER_NONE,
    MANAGER_QUIT
} MANAGER_EVENT;

typedef struct guiManager {
    CHESS_MATCH *match;
    WINDOWS_STACK *stack;
    MOVES_STACK *movesStack;
    GENERIC_WINDOW *genericWindow;
} GUI_MANAGER;

GUI_MANAGER *createManager(SDL_Window *window, SDL_Renderer *renderer);
void destroyManager(GUI_MANAGER *manager);

MANAGER_EVENT managerEventHandler(GUI_MANAGER *manager, SDL_Event *event);

GENERIC_WINDOW *createWindowFromType(WINDOW_TYPE type, GUI_MANAGER *manager);

#endif //PROJECT_GUIMANAGER_H
