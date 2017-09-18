//
// Created by okleinfeld on 9/11/17.
//

#ifndef PROJECT_LOADGAMES_H
#define PROJECT_LOADGAMES_H

#include "GenericWindow.h"
#include "../MatchManagement.h"

#define WINDOW_MIDDLE_X_POS (WINDOW_WIDTH - BUTTON_WIDTH) / 2

/**
 * The drawer function for Load window.
 * @param genericWindow
 * @param match
 * @return 1 on success
 */
int drawLoadGameWindow(GENERIC_WINDOW *genericWindow, SDL_Window *sdlWindow, SDL_Renderer *renderer, CHESS_MATCH *match);

/**
 * The slot button function, created disabled by deafault
 * @param widget
 * @param renderer
 * @return 1 on success
 */
int createDisabledLoadGameButton(WIDGET *widget, SDL_Renderer *renderer);

/**
 * The "create" button function
 * @param widget
 * @param renderer
 * @return 1 on success
 */
int createGameSlotButton(WIDGET *widget, SDL_Renderer *renderer, int slotNum);

/**
 * The Load window event handler
 * @param window
 * @param event
 * @param match
 * @param stack
 * @return the response for GUI manager
 */
EVENT_RESPONSE *loadGameWindowEventHandler(GENERIC_WINDOW *window, SDL_Event *event, CHESS_MATCH *match, MOVES_STACK *stack);

/**
 * Calculates the actual filepath of the button
 * @param allocStr
 * @param slotNum
 */
void getGameSlotButtonPath(char *allocStr, int slotNum);

/**
 * Calculates the height of a certain slot
 * @param slotNum
 * @return the y position
 */
int getGameSlotButtonYposition(int slotNum);

/**
 * Performs the actual load, namely the deep copy
 * @param existingMatch
 * @param loadedMatch
 */
void deepCopyFromLoadedMatch(CHESS_MATCH *existingMatch, CHESS_MATCH *loadedMatch);

#endif //PROJECT_LOADGAMES_H

