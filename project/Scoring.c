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

int countPossibleMoves(CHESS_GAME *game) {
    int count = 0;

    for (int x = 0; x < nRows; x++) {
        for (int y = 0; y < nCols; y++) {
            char piece = matGet(game->gameBoard, x, y);
            if (piece >= 'a' && piece <= 'z') { // piece is white
                MATRIX *possibleMoves = piecePossibleMoves(game, piece, x, y, true);
                for (int i = 0; i < nRows; i++) {
                    for (int j = 0; j < nRows; j++) {
                        count += (int) (matGet(possibleMoves, i, j));
                    }
                }
                matDestroy(possibleMoves);
            }
            else if (piece >= 'A' && piece <= 'Z') { // piece is black
                MATRIX *possibleMoves = piecePossibleMoves(game, piece, x, y, true);
                for (int i = 0; i < nRows; i++) {
                    for (int j = 0; j < nRows; j++) {
                        count -= (int) (matGet(possibleMoves, i, j));
                    }
                }
                matDestroy(possibleMoves);
            }

        }
    }

    return count;
}

int pawnStructure(CHESS_GAME *game) {
    int defendedPawns = 0;

    for (int x = 0; x < nRows; x++) {
        for (int y = 0; y < nCols; y++) {
            char piece = matGet(game->gameBoard, x, y);
            if (piece == 'm') { // black pawn
                int adjRow = x + 1;
                int adjRight = y + 1;
                int adjLeft = y - 1;

                if (!isOutOfBounds(adjRow, adjLeft)) defendedPawns -= 1;
                if (!isOutOfBounds(adjRow, adjRight)) defendedPawns -= 1;

            }
            else if (piece == 'M') { // white pawn
                int adjRow = x - 1;
                int adjRight = y + 1;
                int adjLeft = y - 1;

                if (!isOutOfBounds(adjRow, adjLeft)) defendedPawns += 1;
                if (!isOutOfBounds(adjRow, adjRight)) defendedPawns += 1;
            }
        }
    }

    return defendedPawns;
}

int expertScore(CHESS_GAME *game) {
    int expertModeScore = 0;

    // combine naive scoring function with expert scoring function. give a different weight to each scoring function
    expertModeScore += 100 * score(game); // original score function gets weight 100
    expertModeScore += 50 * countPossibleMoves(game); // it's important to have a more possible moves than the opponent, weight is 50
    expertModeScore += 10 * isGameCheck(game, game->currentPlayer); // The current player is switched before the move, so increment if the player is checked
    expertModeScore += 5 * pawnStructure(game); // defended pawns are a goal when all other moves lead to the same score

    return expertModeScore;
}
