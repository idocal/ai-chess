//
// Created by Ido on 9/11/17.
//

#include "GameAuxGUI.h"

void moveToPosition(CHESS_GAME *game, GENERIC_WINDOW *window, WIDGET *widget, int x, int y, MOVES_STACK *stack) {
    char player = game->currentPlayer;
    int sourceRow = widget->position->row;
    int sourceCol = widget->position->col;

    BOARD_POSITION *newPosition = calculateBoardPosition(x, y);
    GAME_MOVE *move = createGameMove(game, sourceRow, sourceCol, newPosition->row, newPosition->col); // Create move from original to <x,y>

    // Perform move if it's a legal one
    if (move == NULL) {
        widget->rect.x = screenPositionX(widget->position->col);
        widget->rect.y = screenPositionY(widget->position->row);
        reRenderWindow(window);
        return;
    }
    else if (!isSlotOccupied(game, move->sourceRowIndex, move->sourceColIndex, player)) {
        widget->rect.x = screenPositionX(widget->position->col);
        widget->rect.y = screenPositionY(widget->position->row);
        reRenderWindow(window);
        return;
    }
    else if (!isMoveLegal(game, move)) {
        widget->rect.x = screenPositionX(widget->position->col);
        widget->rect.y = screenPositionY(widget->position->row);
        reRenderWindow(window);
        return;
    }
    else {
        // Update widget with new position
        widget->position->row = newPosition->row;
        widget->position->col = newPosition->col;

        // Move widget to screen position
        widget->rect.x = screenPositionX(newPosition->col);
        widget->rect.y = screenPositionY(newPosition->row);
        reRenderWindow(window);

        // Perform move on game representation
        performMove(game, move);
        push(stack, move);
    }

    free(newPosition);
}