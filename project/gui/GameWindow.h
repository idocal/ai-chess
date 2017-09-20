//
// Created by Ido on 9/10/17.
//

#ifndef PROJECT_GAMEWINDOW_H
#define PROJECT_GAMEWINDOW_H

#include "GameAuxGUI.h"

/**
 * The drawer function for Game window.
 * @param genericWindow
 * @param match
 * @return 1 on success
 */
int drawGameWindow(GENERIC_WINDOW *genericWindow, SDL_Window *, SDL_Renderer *, CHESS_MATCH *match);

/**
 * The board function
 * @param widget
 * @param renderer
 * @return 1 on success
 */
int createBoard(WIDGET *widget, SDL_Renderer *renderer);

/**
 * The "restart" button function
 * @param widget
 * @param renderer
 * @return 1 on success
 */
int createRestartButton(WIDGET *widget, SDL_Renderer *renderer);

/**
 * The "save" button function
 * @param widget
 * @param renderer
 * @return 1 on success
 */
int createSaveButton(WIDGET *widget, SDL_Renderer *renderer);

/**
 * The "load" button function
 * @param widget
 * @param renderer
 * @return 1 on success
 */
int createLoadButtonGame(WIDGET *widget, SDL_Renderer *renderer);

/**
 * The "undo" button function
 * @param widget
 * @param renderer
 * @return 1 on success
 */
int createUndoButton(WIDGET *widget, SDL_Renderer *renderer);

/**
 * The "main menu" button function
 * @param widget
 * @param renderer
 * @return 1 on success
 */
int createMenuButton(WIDGET *widget, SDL_Renderer *renderer);

/**
 * The "exit" button function
 * @param widget
 * @param renderer
 * @return 1 on success
 */
int createExitButtonGame(WIDGET *widget, SDL_Renderer *renderer);

/**
 * The Game window event handler
 * @param window
 * @param event
 * @param match
 * @param stack
 * @return the response for GUI manager
 */
EVENT_RESPONSE *gameWindowEventHandler(GENERIC_WINDOW *window, SDL_Event *event, CHESS_MATCH *match, MOVES_STACK *stack);

/**
 * A function to only handle a piece move event
 * @param window
 * @param event
 * @param match
 * @param stack
 * @return true iff move was successfully done
 */
bool handlePieceEvent(GENERIC_WINDOW *window, CHESS_MATCH *match, MOVES_STACK *stack, int widgetIndex);

/**
 * Handles the "get moves" bonus presentation
 * @param game
 * @param row
 * @param col
 * @param window
 * @param difficulty
 */
void handleGetMoves(CHESS_GAME *game, int row, int col, GENERIC_WINDOW *window, int difficulty);

/**
 * Handle save game options
 * @param loadFromIndex
 * @param loadTwoIndex
 * @return 0 on success, -1 on failure
 */
int swapBetweenAdjacentSavedGames(int loadFromIndex, int loadTwoIndex);

/**
 * prompt a message box to for the user to choose whether to continue without saving or go
 * back and save to game.
 * @return
 * 1 if the user wishes to continue without saving (clicked "yes")
 * 0 if the user wishes to go back and save his game before proceeding ("no" or "cancel")
 * -1 if an error occurred
 */

int displayQuitWithoutSaveMessageBox();

#endif //PROJECT_GAMEWINDOW_H
