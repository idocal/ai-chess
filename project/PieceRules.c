//
// Created by Ido on 8/12/17.
//

#include "PieceRules.h"

PIECE pieceByLocation(CHESS_GAME *game, GAME_MOVE *move) {
    if (game == NULL || move == NULL) {
        return BLANK;
    }

    int x = move->sourceRowIndex;
    int y = move->sourceColIndex;

    char pieceChar = matGet(game->gameBoard, x, y);
    PIECE piece;

    switch(pieceChar) {
        case 'm' :
            piece = PAWN;
            break;

        case 'M' :
            piece = PAWN;
            break;

        case 'b' :
            piece = BISHOP;
            break;

        case 'B' :
            piece = BISHOP;
            break;

        case 'r' :
            piece = ROOK;
            break;

        case 'R' :
            piece = ROOK;
            break;

        case 'n' :
            piece = KNIGHT;
            break;

        case 'N' :
            piece = KNIGHT;
            break;

        case 'q' :
            piece = QUEEN;
            break;

        case 'Q' :
            piece = QUEEN;
            break;

        case 'k' :
            piece = KING;
            break;

        case 'K' :
            piece = KING;
            break;

        default :
            piece = BLANK;
    }

    return piece;
}

char **pawnPossibleMoves(CHESS_GAME *game, int x, int y) {
    // Dynamically allocate a matrix
    char (*movesMatrix)[nRows] = calloc(1 ,sizeof(char[nRows][nCols]));

    if (movesMatrix == NULL)


    return movesMatrix;

}
