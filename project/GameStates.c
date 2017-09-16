//
// Created by Ido on 8/19/17.
//

#include "GameStates.h"

bool existsPossibleMove(CHESS_GAME *game) {
    MATRIX *board = game->gameBoard;
    char playerChecked = game->currentPlayer;

    // scan board for opponent pieces and check their possibilities
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            char piece = matGet(board, i, j);
            if (pieceOwner(piece, playerChecked) == 1) { // piece owner is player
                MATRIX *pieceMoves = piecePossibleMoves(game, piece, i, j, true); // piece possibilities matrix

                // check pieceMoves matrix for a possible move. if exists - this means player can avoid check.
                for (int x =0; x < nRows; x++) {
                    for (int y = 0; y < nCols; y++) {
                        if (matGet(pieceMoves, x, y)) {
                            matDestroy(pieceMoves);
                            return true;
                        }

                    }
                }

                matDestroy(pieceMoves);
            }
        }
    }

    return false;
}

bool isCheck(CHESS_GAME *game) {
    return isGameCheck(game, game->currentPlayer);
}

bool isCheckMate(CHESS_GAME *game) {
    if (!isCheck(game)) return false;
    return !existsPossibleMove(game);
}

bool isTie(CHESS_GAME *game) {
    return !existsPossibleMove(game);
}

void updateGameState(CHESS_GAME *game) {
    if (isCheckMate(game)) game->status = MATE;
    else if (isCheck(game)) game->status = CHECK;
    else if (isTie(game)) game->status = TIE;
    else game->status = REGULAR;
}
