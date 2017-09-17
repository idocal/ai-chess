//
// Created by Ido on 9/9/17.
//

#ifndef PROJECT_WELCOMEWINDOW_H
#define PROJECT_WELCOMEWINDOW_H

#include "GenericWindow.h"

#define WELCOME_WINDOW_MIDDLE_X_POS (WINDOW_WIDTH - BUTTON_WIDTH) / 2

typedef enum welcomeWidget {
    WELCOME_NEW_GAME,
    WELCOME_LOAD_GAME,
    WELCOME_EXIT,
    WELCOME_NONE
} WELCOME_WIDGET;


/**
 * The drawer function for Welcome window.
 * @param genericWindow
 * @param match
 * @return 1 on success
 */
int drawWelcomeWindow(GENERIC_WINDOW *genericWindow, SDL_Window *sdlWindow, SDL_Renderer *renderer, CHESS_MATCH *match);

/**
 * The "new game" button function
 * @param widget
 * @param renderer
 * @return 1 on success
 */
int createNewGameButton(WIDGET *widget, SDL_Renderer *renderer);

/**
 * The "load" button function
 * @param widget
 * @param renderer
 * @return 1 on success
 */
int createLoadWelcomeButton(WIDGET *widget, SDL_Renderer *renderer);

/**
 * The "exit" button function
 * @param widget
 * @param renderer
 * @return 1 on success
 */
int createExitWelcomeButton(WIDGET *widget, SDL_Renderer *renderer);

/**
 * The Welcome window event handler
 * @param window
 * @param event
 * @param match
 * @param stack
 * @return the response for GUI manager
 */
EVENT_RESPONSE *welcomeWindowEventHandler(GENERIC_WINDOW *window, SDL_Event *event, CHESS_MATCH *match, MOVES_STACK *stack);

#endif //PROJECT_WELCOMEWINDOW_H
