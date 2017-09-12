//
// Created by Ido on 9/11/17.
//

#ifndef PROJECT_GAMEAUXGUI_H
#define PROJECT_GAMEAUXGUI_H

#define screenPositionX(col) (initialX + 80 * col)
#define screenPositionY(row) (initialBlackY + 80 * (7 - row))

#define playerColor(player) ((player == 1) ? "Black player won" : "White player won")

#include "../GameMoves.h"
#include "../GameAux.h"
#include "PiecesWidget.h"
#include "Widget.h"

int moveToPosition(CHESS_GAME *game, GENERIC_WINDOW *window, WIDGET *widget, int x, int y, MOVES_STACK *stack);

void swapTurns(CHESS_MATCH *match, MOVES_STACK *stack, GENERIC_WINDOW *window);
int handleAIMove(CHESS_MATCH *match, MOVES_STACK *stack, GENERIC_WINDOW *window);
WIDGET *findWidget(GENERIC_WINDOW *window, int x, int y);

void handleWin(char playerWon);
void handleTie();

void hidePiece(WIDGET *widget);

void handleUndo(CHESS_GAME *game, MOVES_STACK *stack, GENERIC_WINDOW *window);
void revertMoveGUI(CHESS_GAME *game, GAME_MOVE *move, GENERIC_WINDOW *window, MOVES_STACK *stack);
int gameMoveToBoardMove(GAME_MOVE *move, GENERIC_WINDOW *window, MOVES_STACK *stack, CHESS_GAME *game);

#endif //PROJECT_GAMEAUXGUI_H
