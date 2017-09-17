//
// Created by Ido on 9/10/17.
//

#ifndef PROJECT_DIFFICULTYWINDOW_H
#define PROJECT_DIFFICULTYWINDOW_H

#include "GenericWindow.h"
#include "../MatchManagement.h"

/**
 * The drawer function for Choose Difficulty window.
 * @param genericWindow
 * @param match
 * @return 1 on success
 */
int drawDifficultyWindow(GENERIC_WINDOW *genericWindow, SDL_Window *, SDL_Renderer *, CHESS_MATCH *match);

/**
 * The title for Choose Difficulty window function
 * @param widget
 * @param renderer
 * @return 1 on success
 */
int createDifficultyTitle(WIDGET *widget, SDL_Renderer *renderer);


/**
 * The "noob" button function
 * @param widget
 * @param renderer
 * @return 1 on success
 */
int createNoobButton(WIDGET *widget, SDL_Renderer *renderer);

/**
 * The "easy" button function
 * @param widget
 * @param renderer
 * @return 1 on success
 */
int createEasyButton(WIDGET *widget, SDL_Renderer *renderer);

/**
 * The "moderate" button function
 * @param widget
 * @param renderer
 * @return 1 on success
 */
int createModerateButton(WIDGET *widget, SDL_Renderer *renderer);

/**
 * The "hard" button function
 * @param widget
 * @param renderer
 * @return 1 on success
 */
int createHardButton(WIDGET *widget, SDL_Renderer *renderer);

/**
 * The "expert" button function
 * @param widget
 * @param renderer
 * @return 1 on success
 */
int createExpertButton(WIDGET *widget, SDL_Renderer *renderer);

/**
 * The Choose Difficulty window event handler
 * @param window
 * @param event
 * @param match
 * @param stack
 * @return the response for GUI manager
 */
EVENT_RESPONSE *difficultyWindowEventHandler(GENERIC_WINDOW *window, SDL_Event *event, CHESS_MATCH *match, MOVES_STACK *stack);

#endif //PROJECT_DIFFICULTYWINDOW_H
