//
// Created by okleinfeld on 7/27/2017.
//

#include "GameRepresenation.h"

CHESS_GAME* createEmptyGame(){
    CHESS_GAME *game = (CHESS_GAME *) malloc(sizeof(CHESS_GAME));
    if (game == NULL){
        return NULL;
    }

    // default settings are regular status, white player turn empty board (no tools at all)
    game->status = REGULAR;
    game->currentPlayer = 1;

    // game board is a rows * cols matrix
    game->gameBoard = matNew(nRows, nCols);
    if (game->gameBoard == NULL){
        free(game);
        return NULL;
    }

    // fill game board with blanks
    for(int i = 0; i < nRows; ++i){
        for (int j = 0; j < nCols; ++j){
            matSet(game->gameBoard, i, j, '_');
        }
    }
    return game;
}

CHESS_GAME* copyChessGame(CHESS_GAME *originalGame){
    CHESS_GAME *cpyGame = createEmptyGame(); // allocate memory for new object
    if (cpyGame == NULL){
        return NULL;
    }
    cpyGame->status = originalGame->status;
    cpyGame->currentPlayer = originalGame->currentPlayer;
    for (int i = 0; i < nRows; ++i){
        for (int j = 0; j < nCols; ++j){
            char originalVal = matGet(originalGame->gameBoard, i, j);
            matSet(cpyGame->gameBoard, i, j, originalVal);
        }
    }
    return cpyGame;
}

void destroyChessGame(CHESS_GAME *game){
    if (game == NULL){
        return;
    }
    free(game->gameBoard); // then free the pointers array
    free(game); // at last free the object itself.
}

void initGameBoard(CHESS_GAME *game){
    if (game == NULL){
        return;
    }

    MATRIX *board = game->gameBoard;

    // white player pieces
    matSet(board, 0, 0, 'r');
    matSet(board, 0, 1, 'n');
    matSet(board, 0, 2, 'b');
    matSet(board, 0, 3, 'q');
    matSet(board, 0, 4, 'k');
    matSet(board, 0, 5, 'b');
    matSet(board, 0, 6, 'n');
    matSet(board, 0, 7, 'r');

    // black player pieces
    matSet(board, 7, 0, 'R');
    matSet(board, 7, 1, 'N');
    matSet(board, 7, 2, 'B');
    matSet(board, 7, 3, 'Q');
    matSet(board, 7, 4, 'K');
    matSet(board, 7, 5, 'B');
    matSet(board, 7, 6, 'N');
    matSet(board, 7, 7, 'R');

    // white and black player pawns
    for (int i = 0; i < nCols; ++i){
        matSet(board, 1, i, 'm');
        matSet(board, 6, i, 'M');
    }
}

void printChessGameBoard(CHESS_GAME *game){
    if (game == NULL){
        return;
    }
    for (int i = nRows; i > 0; --i){
        printf("%d|",i);
        for (int j = 0; j < nCols; ++j){
            printf(" %c", matGet(game->gameBoard, i-1, j));
        }
        printf(" |\n");
    }
    printf("  ");
    for (int k = 0; k < 17; ++k){
        printf("-");
    }
    printf("\n");
    char startCol = 'A';
    printf("  ");
    for (int m = 0; m < nCols; ++m){
        printf(" %c", startCol + m);
    }
}

GAME_MOVE *createGameMove(CHESS_GAME *game, int source_row, int source_col, int dest_row, int dest_col){
    if (game == NULL){
        return NULL;
    }
    GAME_MOVE *move = (GAME_MOVE *) malloc(sizeof(GAME_MOVE));
    if (move == NULL){
        return NULL;
    }
    move->sourceRowIndex = source_row;
    move->sourceColIndex = source_col;
    move->destRowIndex = dest_row;
    move->destColIndex = dest_col;
    move->sourceOriginalSymbol = matGet(game->gameBoard, source_row, source_col);
    move->destOriginalSymbol = matGet(game->gameBoard, dest_row, dest_col);
    return move;
}

void destroyGameMove(GAME_MOVE *move){
    if (move == NULL){
        return;
    }
    free(move);
}