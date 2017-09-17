//
// Created by Ido on 9/11/17.
//

#ifndef PROJECT_GAMEAUXGUI_H
#define PROJECT_GAMEAUXGUI_H

#define playerColor(player) ((player == 1) ? "Black player won" : "White player won")

#include "../GameMoves.h"
#include "../GameAux.h"
#include "PiecesWidget.h"
#include "Widget.h"

/**
 * Performs an actual move on the board, including a move on the game board representation
 * @param game
 * @param window
 * @param widget
 * @param x
 * @param y
 * @param stack
 * @return 1 on success, -1 on failure
 */
int moveToPosition(CHESS_GAME *game, GENERIC_WINDOW *window, WIDGET *widget, int x, int y, MOVES_STACK *stack);

/**
 * Swaps turns upon move completion, including performance of AI move
 * @param window
 * @param event
 * @param match
 * @param stack
 * @return true iff turns were successfully swapped
 */
bool swapTurns(CHESS_MATCH *match, MOVES_STACK *stack, GENERIC_WINDOW *window);

/**
 * Performs the AI move.
 * @param match
 * @param stack
 * @param window
 * @return 1 on success, -1 on failure
 */
int handleAIMove(CHESS_MATCH *match, MOVES_STACK *stack, GENERIC_WINDOW *window);

/**
 * Special function for AI as white player
 * @param match
 * @param window
 * @return 1 on success, -1 on failure
 */
int handleAIFirstMove(CHESS_MATCH *match, GENERIC_WINDOW *window);

/**
 * Find the widget that is both clickable and positioned in <x,y>.
 * <x,y> is the screen position and not <row,col> board representation
 * @param window
 * @param x
 * @param y
 * @return Ptr to the found widget
 */
WIDGET *findWidget(GENERIC_WINDOW *window, int x, int y);

/**
 * Same as find widget but returns the widget index of window->widgets
 * @param window
 * @param x
 * @param y
 * @return found widget index or -1 on failure
 */
int findWidgetIndex(GENERIC_WINDOW *window, int x, int y);

/**
 * Shows win message on the screen
 * @param playerWon
 */
void handleWin(char playerWon);

/**
 * Shows tie message on the screen
 */
void handleTie();

/**
 * Hides a piece from window. this is been done by moving to position <-80, -80>
 * @param widget
 */
void hidePiece(WIDGET *widget);

/**
 * Handles the undo including undoing AI moves
 * @param game
 * @param stack
 * @param window
 */
void handleUndo(CHESS_GAME *game, MOVES_STACK *stack, GENERIC_WINDOW *window);

/**
 * Performs the GUI actions of undo move
 * @param game
 * @param move
 * @param window
 * @param stack
 */
void revertMoveGUI(CHESS_GAME *game, GAME_MOVE *move, GENERIC_WINDOW *window, MOVES_STACK *stack);

/**
 * Translates a GAME_MOVE to board move on GUI
 * @param move
 * @param window
 * @param stack
 * @param game
 * @return 1 on success
 */
int gameMoveToBoardMove(GAME_MOVE *move, GENERIC_WINDOW *window, MOVES_STACK *stack, CHESS_GAME *game);

#endif //PROJECT_GAMEAUXGUI_H
