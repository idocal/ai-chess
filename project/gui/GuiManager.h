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

/**
 * Creates the GUI manager
 * @param window
 * @param renderer
 * @return Ptr to the created manager
 */
GUI_MANAGER *createManager(SDL_Window *window, SDL_Renderer *renderer);

/**
 * Destroys the maanger
 * @param manager
 */
void destroyManager(GUI_MANAGER *manager);

/**
 * Event handler for the manager.
 * This is the decision maker that deals with window responses
 * @param manager
 * @param event
 * @return the manager_event that reports to MAIN (quit or continue)
 */
MANAGER_EVENT managerEventHandler(GUI_MANAGER *manager, SDL_Event *event);

/**
 * Creates a GENERIC_WINDOW by it's type
 * @param type
 * @param manager
 * @return Ptr to the created window
 */
GENERIC_WINDOW *createWindowFromType(WINDOW_TYPE type, GUI_MANAGER *manager);

#endif //PROJECT_GUIMANAGER_H
