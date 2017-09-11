//
// Created by Ido on 9/9/17.
//

#include "GenericWindow.h"
#include "WelcomeWindow.h"
#include "WindowsStack.h"

#ifndef PROJECT_GUIMANAGER_H
#define PROJECT_GUIMANAGER_H

typedef enum {
    MANAGER_NONE,
    MANAGER_QUIT
} MANAGER_EVENT;

typedef struct guiManager {
    GENERIC_WINDOW *genericWindow;
    CHESS_MATCH *match;
    WINDOWS_STACK *stack;
    MOVES_STACK *movesStack;
} GUI_MANAGER;

GUI_MANAGER *createManager(SDL_Window *window, SDL_Renderer *renderer);
void destroyManager(GUI_MANAGER *manager);

MANAGER_EVENT managerEventHandler(GUI_MANAGER *manager, SDL_Event *event);

#endif //PROJECT_GUIMANAGER_H
