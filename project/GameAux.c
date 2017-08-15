//
// Created by Ido on 8/13/17.
//

#include "GameAux.h"

void performMove(CHESS_GAME *game, GAME_MOVE *move) {
    MATRIX *board = game->gameBoard;
    char piece = matGet(board, move->sourceRowIndex, move->sourceColIndex); // get the piece on previous cell
    matSet(board, move->sourceRowIndex, move->sourceColIndex, '_'); // fill blank on previous cell
    matSet(board, move->destRowIndex, move->destColIndex, piece); // set piece on current cell
}