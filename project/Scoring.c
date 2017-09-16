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

int expertPieceLegend(char piece) {
    if (piece == 'r' || piece == 'R') return 5;
    if (piece == 'n' || piece == 'N' || piece == 'b' || piece == 'B') return 5;
    if (piece == 'q' || piece == 'Q') return 9;
    if (piece == 'k' || piece == 'K') return 15;
    return 0; // have to add this in order to compile the code under Werror flag
}

int threatenedScore(CHESS_GAME *game, char player) {
    MATRIX *board = game->gameBoard;
    int score = 0;
    for (int x = 0; x < nRows; x++) {
        for (int y = 0; y < nCols; y++) {
            char piece = matGet(board, x, y);
            if (pieceOwner(piece, player) == 1 && piece != 'm' && piece != 'M') { // not checking pawns
                int pieceThreatenedCounter = 0;
                for (int i = 0; i < nRows; i++) {
                    for (int j = 0; j < nCols; j++) {
                        char opponentPiece = matGet(board, i, j);
                        char opponent = opponent(player);
                        if (pieceOwner(opponentPiece, opponent) == 1) { // check opponent piece possible moves
                            MATRIX *possibleMoves = piecePossibleMoves(game, opponentPiece, i, j, true);
                            pieceThreatenedCounter += matGet(possibleMoves, x, y); // if possible move is (x,y) add to counter
                            matDestroy(possibleMoves);
                        }
                    }
                }

                score += expertPieceLegend(piece) * pieceThreatenedCounter;

            }

        }
    }
    return score;
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

int expertScore(CHESS_GAME *game) {
    int expertModeScore = 0;

    // combine naive scoring function with expert scoring function. give a different weight to each scoring function
    expertModeScore += 3 * score(game); // original score function gets weight 3
    expertModeScore += threatenedScore(game, opponent(game->currentPlayer));
    expertModeScore -= threatenedScore(game, game->currentPlayer);

    return expertModeScore;
}