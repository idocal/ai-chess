//
// Created by Ido on 8/12/17.
//

#include "PieceRules.h"

char pieceOwner(char piece, char player) {
    if (piece == '_') return -1;

    // define range for pieces symbols,
    // if black (0) - 'A'-'Z' , if white (1) - 'a'-'z'
    char delta = (char) ('a' - 'A'); // a comes after A in ASCII
    char lowerBound = (char) ('A' + player * delta);
    char upperBound = (char) ('Z' + player * delta);

    // if piece is in player's range
    if (piece >= lowerBound && piece <= upperBound) return 1;

    // else piece is opponent's
    return 0;
}

bool isPawnInitialLocation(char player, int x) {
    if (player == 0 && x == 6) return true;
    else if (player == 1 && x == 1) return true;
    return false;
}

bool isOutOfBounds(int x, int y) {
    if (x > 7 || x < 0 || y > 7 || y < 0) return true;
    return false;
}

bool isSlotOccupied(CHESS_GAME *game, int x, int y, char playerMoved) {
    MATRIX *board = game->gameBoard;
    char slot = matGet(board, x, y);

    // if slot piece owner is player (1)
    if (pieceOwner(slot, playerMoved) == 1) return true;

    // else slot piece is either _ or opponent's
    return false;
}

bool isGameCheck(CHESS_GAME *game, char playerChecked) {
    MATRIX *board = game->gameBoard;
    char king = (playerChecked == 1) ? (char) ('k') : (char) ('K');
    int kingX = 0;
    int kingY = 0;

    // scan board for player's king location <kingX, kingY>
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            if (matGet(board, i, j) == king) {
                kingX = i;
                kingY = j;
            }
        }
    }

    // scan board for opponent pieces and check their possibilities
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            char piece = matGet(board, i, j);
            if (pieceOwner(piece, playerChecked) == 0) { // piece owner is opponent
                MATRIX *pieceMoves = piecePossibleMoves(game, piece, i, j, false); // piece possibilities matrix
//                printf("Calling piece moves for: %c\n", piece);
                if (matGet(pieceMoves, kingX, kingY) == 1) { // if king's location is a possible move - player is Checked.
                    matDestroy(pieceMoves);
                    return true;
                }
                matDestroy(pieceMoves);
            }
        }
    }

    return false;
}

bool isMovePossible(CHESS_GAME *game, GAME_MOVE *move, char player, bool includeCheck) {
    int x = move->destRowIndex;
    int y = move->destColIndex;

    // check if <x,y> is out of the board, or slot is occupied by player's piece
    if (isOutOfBounds(x, y) || isSlotOccupied(game, x, y, player)) {
        destroyGameMove(move);
        destroyChessGame(game);
        return false;
    }

    // if possibility of the move depends on Check, perform the move and decide if player would be Checked
    if (includeCheck) {
        performMove(game, move);

        // if game after move leads to Check of the player moved, move is impossible
        if (isGameCheck(game, player)) {
            destroyGameMove(move);
            destroyChessGame(game);
            return false;
        }
    }

    // otherwise move is OK
    destroyGameMove(move);
    destroyChessGame(game);
    return true;
}

void testPossibility(MATRIX *movesMatrix, CHESS_GAME *game, int x, int x_, int y, int y_, char player, bool includeCheck, int marker) {
    CHESS_GAME *cpyGame = copyChessGame(game);
    GAME_MOVE *newMove = createGameMove(cpyGame, x_, y_, x, y);

    if (isMovePossible(cpyGame, newMove, player, includeCheck)) {
        matSet(movesMatrix, x, y, marker); // set 1 on moves matrix if the move is possible
    }
}

void linearMoves(MATRIX *movesMatrix, CHESS_GAME *game, int x, int y, char player, bool includeCheck, int right, int up) {
    MATRIX *board = game->gameBoard;

    int i = 1;
    CHESS_GAME *cpyGame = copyChessGame(game);
    GAME_MOVE *newMove = createGameMove(cpyGame, x, y, x + right * i, y + up * i);

    while (isMovePossible(cpyGame, newMove, player, includeCheck)) { // stop going when a move is impossible
        matSet(movesMatrix, x + right * i, y + up * i, 1);

        // if slot is a conquering one, stop going
        char piece = matGet(board, x + right * i, y + up * i);
        if (pieceOwner(piece, player) == 0) break;

        i++;
        cpyGame = copyChessGame(game);
        newMove = createGameMove(cpyGame, x, y, x + right * i, y + up * i);
    }
}

void addOrthogonalMoves(MATRIX *movesMatrix, CHESS_GAME *game, int x, int y, char player, bool includeCheck) {
    // add rightward slots
    linearMoves(movesMatrix, game, x, y, player, includeCheck, 1, 0);

    // add leftward slots
    linearMoves(movesMatrix, game, x, y, player, includeCheck, -1, 0);

    // add upward slots
    linearMoves(movesMatrix, game, x, y, player, includeCheck, 0, 1);

    // add downward slots
    linearMoves(movesMatrix, game, x, y, player, includeCheck, 0, -1);
}

void addDiagonalMoves(MATRIX *movesMatrix, CHESS_GAME *game, int x, int y, char player, bool includeCheck) {
    // add right-upward slots
    linearMoves(movesMatrix, game, x, y, player, includeCheck, 1, 1);

    // add right-downward slots
    linearMoves(movesMatrix, game, x, y, player, includeCheck, 1, -1);

    // add left-upward slots
    linearMoves(movesMatrix, game, x, y, player, includeCheck, -1, 1);

    // add left-downward slots
    linearMoves(movesMatrix, game, x, y, player, includeCheck, -1, -1);
}

MATRIX *piecePossibleMoves(CHESS_GAME *game, char piece, int x, int y, bool includeCheck) {
    switch(piece) {
        case 'm' :
            return pawnPossibleMoves(game, x, y, 1, includeCheck);

        case 'M' :
            return pawnPossibleMoves(game, x, y, 0, includeCheck);

        case 'b' :
            return bishopPossibleMoves(game, x, y, 1, includeCheck);

        case 'B' :
            return bishopPossibleMoves(game, x, y, 0, includeCheck);

        case 'r' :
            return rookPossibleMoves(game, x, y, 1, includeCheck);

        case 'R' :
            return rookPossibleMoves(game, x, y, 0, includeCheck);

        case 'n' :
            return knightPossibleMoves(game, x, y, 1, includeCheck);

        case 'N' :
            return knightPossibleMoves(game, x, y, 0, includeCheck);

        case 'q' :
            return queenPossibleMoves(game, x, y, 1, includeCheck);

        case 'Q' :
            return queenPossibleMoves(game, x, y, 0, includeCheck);

        case 'k' :
            return kingPossibleMoves(game, x, y, 1, includeCheck);

        case 'K' :
            return kingPossibleMoves(game, x, y, 0, includeCheck);

        default :
            return NULL;
    }
    return NULL;
}

MATRIX *pawnPossibleMoves(CHESS_GAME *game, int x, int y, char player, bool includeCheck) {
    MATRIX *movesMatrix = matNew(nRows, nCols);
    if (movesMatrix == NULL) {
        return NULL;
    }

    MATRIX *board = game->gameBoard;
    int moveOne = x + player + (-1 * (1 - player)); // white player moves to x+1, black player moves to x-1
    int moveTwo = x + 2 * player + (-2 * (1 - player)); // white player moves to x+2, black player moves to x-2

    // move one forward
    testPossibility(movesMatrix, game, moveOne, x, y, y, player, includeCheck, 1);

    // move two forward
    if (isPawnInitialLocation(player, x))
        testPossibility(movesMatrix, game, moveTwo, x, y, y, player, includeCheck, 1);

    // apply diagonal conquer moves
    testPossibility(movesMatrix, game, moveOne, x, y+1, y, player, includeCheck, 2);
    testPossibility(movesMatrix, game, moveOne, x, y-1, y, player, includeCheck, 2);

    // verify that slots do not contain opponent's piece
    for (int i = 0; i < movesMatrix->rows; i++) {
        for (int j = 0; j < movesMatrix->cols; j++) {
            char piece = matGet(board, i, j);
            char current = matGet(movesMatrix, i, j);
            if (pieceOwner(piece, player) == 0) { //piece owner is opponent
                if (current == 2) matSet(movesMatrix, i, j, 1); // conquered slot
                else matSet(movesMatrix, i, j, 0);
            }
            current = matGet(movesMatrix, i, j);
            if (current == 2) matSet(movesMatrix, i, j, 0); //unconquered slot should be removed anyhow
        }
    }

    return movesMatrix;
}

MATRIX *bishopPossibleMoves(CHESS_GAME *game, int x, int y, char player, bool includeCheck) {
    MATRIX *movesMatrix = matNew(nRows, nCols);
    if (movesMatrix == NULL) {
        return NULL;
    }

    addDiagonalMoves(movesMatrix,game, x, y, player, includeCheck);
    return movesMatrix;
}

MATRIX *rookPossibleMoves(CHESS_GAME *game, int x, int y, char player, bool includeCheck) {
    MATRIX *movesMatrix = matNew(nRows, nCols);
    if (movesMatrix == NULL) {
        return NULL;
    }

    addOrthogonalMoves(movesMatrix,game, x, y, player, includeCheck);
    return movesMatrix;
}

MATRIX *knightPossibleMoves(CHESS_GAME *game, int x, int y, char player, bool includeCheck) {
    MATRIX *movesMatrix = matNew(nRows, nCols);
    if (movesMatrix == NULL) {
        return NULL;
    }

    // move two up one right
    testPossibility(movesMatrix, game, x+2, x, y+1, y, player, includeCheck, 1);

    // move two up one left
    testPossibility(movesMatrix, game, x+2, x, y-1, y, player, includeCheck, 1);

    // move two down one right
    testPossibility(movesMatrix, game, x-2, x, y+1, y, player, includeCheck, 1);

    // move two down one left
    testPossibility(movesMatrix, game, x-2, x, y-1, y, player, includeCheck, 1);

    // move two right one up
    testPossibility(movesMatrix, game, x+1, x, y+2, y, player, includeCheck, 1);

    // move two right one down
    testPossibility(movesMatrix, game, x-1, x, y+2, y, player, includeCheck, 1);

    // move two left one up
    testPossibility(movesMatrix, game, x+1, x, y-2, y, player, includeCheck, 1);

    // move two left one down
    testPossibility(movesMatrix, game, x-1, x, y-2, y, player, includeCheck, 1);

    return movesMatrix;
}

MATRIX *queenPossibleMoves(CHESS_GAME *game, int x, int y, char player, bool includeCheck) {
    MATRIX *movesMatrix = matNew(nRows, nCols);
    if (movesMatrix == NULL) {
        return NULL;
    }

    addDiagonalMoves(movesMatrix,game, x, y, player, includeCheck);
    addOrthogonalMoves(movesMatrix,game, x, y, player, includeCheck);

    return movesMatrix;
}

MATRIX *kingPossibleMoves(CHESS_GAME *game, int x, int y, char player, bool includeCheck) {
    MATRIX *movesMatrix = matNew(nRows, nCols);
    if (movesMatrix == NULL) {
        return NULL;
    }

    // move one right
    testPossibility(movesMatrix, game, x, x, y+1, y, player, includeCheck, 1);

    // move one left
    testPossibility(movesMatrix, game, x, x, y-1, y, player, includeCheck, 1);

    // move one up
    testPossibility(movesMatrix, game, x+1, x, y, y, player, includeCheck, 1);

    // move one down
    testPossibility(movesMatrix, game, x-1, x, y, y, player, includeCheck, 1);

    // move one up-right
    testPossibility(movesMatrix, game, x+1, x, y+1, y, player, includeCheck, 1);

    // move one up-left
    testPossibility(movesMatrix, game, x+1, x, y-1, y, player, includeCheck, 1);

    // move one down-right
    testPossibility(movesMatrix, game, x-1, x, y+1, y, player, includeCheck, 1);

    // move one down-left
    testPossibility(movesMatrix, game, x-1, x, y-1, y, player, includeCheck, 1);

    return movesMatrix;
}
