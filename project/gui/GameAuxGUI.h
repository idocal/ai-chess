//
// Created by Ido on 9/11/17.
//

#ifndef PROJECT_GAMEAUXGUI_H
#define PROJECT_GAMEAUXGUI_H

#define screenPositionX(col) (initialX + 80 * col)
#define screenPositionY(row) (initialBlackY + 80 * (7 - row))

#include "../GameMoves.h"
#include "../GameAux.h"
#include "PiecesWidget.h"
#include "Widget.h"

void moveToPosition(CHESS_GAME *game, GENERIC_WINDOW *window, WIDGET *widget, int x, int y, MOVES_STACK *stack);

#endif //PROJECT_GAMEAUXGUI_H
