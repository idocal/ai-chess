//
// Created by Ido on 9/10/17.
//

#ifndef PROJECT_COLORWINDOW_H
#define PROJECT_COLORWINDOW_H

#include "GenericWindow.h"
#include "../MatchManagement.h"

/**
 * The drawer function for Choose Color window.
 * @param genericWindow
 * @param match
 * @return 1 on success
 */
int drawColorWindow(GENERIC_WINDOW *genericWindow, SDL_Window *, SDL_Renderer *, CHESS_MATCH *match);

/**
 * The title for Choose Color window function
 * @param widget
 * @param renderer
 * @return 1 on success
 */
int createColorTitle(WIDGET *widget, SDL_Renderer *renderer);

/**
 * The "choose white" button function
 * @param widget
 * @param renderer
 * @return 1 on success
 */
int createWhiteButton(WIDGET *widget, SDL_Renderer *renderer);

/**
 * The "choose black" button function
 * @param widget
 * @param renderer
 * @return 1 on success
 */
int createBlackButton(WIDGET *widget, SDL_Renderer *renderer);

/**
 * The Choose Color window event handler
 * @param window
 * @param event
 * @param match
 * @param stack
 * @return the response for GUI manager
 */
EVENT_RESPONSE *colorWindowEventHandler(GENERIC_WINDOW *window, SDL_Event *event, CHESS_MATCH *match, MOVES_STACK *stack);

#endif //PROJECT_COLORWINDOW_H
