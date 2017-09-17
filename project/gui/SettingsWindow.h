//
// Created by Ido on 9/9/17.
//

#ifndef PROJECT_SETTINGSMODEWINDOW_H
#define PROJECT_SETTINGSMODEWINDOW_H

#include "GenericWindow.h"
#include "../MatchManagement.h"


/**
 * The drawer function for Mode window.
 * @param genericWindow
 * @param match
 * @return 1 on success
 */
int drawSettingsWindow(GENERIC_WINDOW *genericWindow, SDL_Window *sdlWindow, SDL_Renderer *renderer, CHESS_MATCH *match);

/**
 * The title for Mode window function
 * @param widget
 * @param renderer
 * @return 1 on success
 */
int createGameModeTitle(WIDGET *widget, SDL_Renderer *renderer);

/**
 * The "one player" button function
 * @param widget
 * @param renderer
 * @return 1 on success
 */
int createOnePlayerButton(WIDGET *widget, SDL_Renderer *renderer);

/**
 * The "two" button function
 * @param widget
 * @param renderer
 * @return 1 on success
 */
int createTwoPlayersButton(WIDGET *widget, SDL_Renderer *renderer);

/**
 * The "back" button function
 * @param widget
 * @param renderer
 * @return 1 on success
 */
int createBackButton(WIDGET *widget, SDL_Renderer *renderer);

/**
 * The "start" button function
 * @param widget
 * @param renderer
 * @return 1 on success
 */
int createStartButton(WIDGET *widget, SDL_Renderer *renderer);

/**
 * The "next" button function
 * @param widget
 * @param renderer
 * @return 1 on success
 */
int createNextButton(WIDGET *widget, SDL_Renderer *renderer);

/**
 * The Mode window event handler
 * @param window
 * @param event
 * @param match
 * @param stack
 * @return the response for GUI manager
 */
EVENT_RESPONSE *settingsWindowEventHandler(GENERIC_WINDOW *window, SDL_Event *event, CHESS_MATCH *match, MOVES_STACK *stack);

#endif //PROJECT_SETTINGSMODEWINDOW_H
