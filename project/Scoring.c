//
// Created by Ido on 8/25/17.
//

#include "Scoring.h"

int pieceScore(char piece) {
    switch(piece) {
        case 'm' :
            return 1;

        case 'M' :
            return -1;

        case 'b' :
            return 3;

        case 'B' :
            return -3;

        case 'r' :
            return 5;

        case 'R' :
            return -5;

        case 'n' :
            return 3;

        case 'N' :
            return -3;

        case 'q' :
            return 9;

        case 'Q' :
            return -9;

        case 'k' :
            return 100;

        case 'K' :
            return -100;

        default :
            return 0; // should be blank
    }
}

int score(CHESS_GAME *game) {
    MATRIX *board = game->gameBoard;
    int score = 0;
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            score += pieceScore(matGet(board, i, j));
        }
    }
    return score;
}