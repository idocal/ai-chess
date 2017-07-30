//
// Created by okleinfeld on 7/27/2017.
//

#include "GameRepresenation.h"

CHESS_GAME* createEmptyGame(){
    CHESS_GAME *game = (CHESS_GAME *) malloc(sizeof(CHESS_GAME));
    if (game == NULL){
        return NULL;
    }
    /*
     * default settings are regular status, white player turn empty board (no tools at all)
     */
    game->specialGameStatus = REGULAR;
    game->currentPlayer = 1;
    game->gameBoard = (char **) malloc(nRows * sizeof(int *)); // allocation of pointer array
    if (game->gameBoard == NULL){
        free(game);
        return NULL;
    }
    char *boardMatrix = (char *) malloc(nRows * nCols * sizeof(char)); // allocation of actual matrix
    if (boardMatrix == NULL){
        free(game->gameBoard);
        free(game);
        return NULL;
    }
    for (int i = 0; i < nRows; ++i){
        game->gameBoard[i] = boardMatrix + i * nCols; // connect the pointer array to the matrix rows
    }
    for(int i = 0; i < nRows; ++i){
        for (int j = 0; j < nCols; ++j){
            game->gameBoard[i][j] = '_'; // initiate every matrix cell to represent empty cell
        }
    }
    return game;
}

CHESS_GAME* copyChessGame(CHESS_GAME *originalGame){
    CHESS_GAME *cpyGame = createEmptyGame(); // allocate memory for new object
    if (cpyGame == NULL){
        return NULL;
    }
    cpyGame->specialGameStatus = originalGame->specialGameStatus;
    cpyGame->currentPlayer = originalGame->currentPlayer;
    for (int i = 0; i < nRows; ++i){
        for (int j = 0; j < nCols; ++j){
            cpyGame->gameBoard[i][j] = originalGame->gameBoard[i][j];
        }
    }
    return cpyGame;
}

void destroyChessGame(CHESS_GAME *game){
    if (game == NULL){
        return;
    }
    free(game->gameBoard[0]); // free actual matrix (base address is row 0, which first cell in pointer array points to.
    free(game->gameBoard); // then free the pointers array
    free(game); // at last free the object itself.
}

void initGameBoard(CHESS_GAME *game){
    if (game == NULL){
        return;
    }
    game->gameBoard[0][0] = 'r';
    game->gameBoard[0][1] = 'n';
    game->gameBoard[0][2] = 'b';
    game->gameBoard[0][3] = 'q';
    game->gameBoard[0][4] = 'k';
    game->gameBoard[0][5] = 'b';
    game->gameBoard[0][6] = 'n';
    game->gameBoard[0][7] = 'r';
    game->gameBoard[7][0] = 'R';
    game->gameBoard[7][1] = 'N';
    game->gameBoard[7][2] = 'B';
    game->gameBoard[7][3] = 'Q';
    game->gameBoard[7][4] = 'K';
    game->gameBoard[7][5] = 'B';
    game->gameBoard[7][6] = 'N';
    game->gameBoard[7][7] = 'R';
    for (int i = 0; i < nCols; ++i){
        game->gameBoard[1][i] = 'p';
        game->gameBoard[6][i] = 'P';
    }
}

void printChessGameBoard(CHESS_GAME *game){
    if (game == NULL){
        return;
    }
    for (int i = nRows; i > 0; --i){
        printf("%d|",i);
        for (int j = 0; j < nCols; ++j){
            printf(" %c", game->gameBoard[i-1][j]);
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
    move->soucreColIndex = source_col;
    move->destRowIndex = dest_row;
    move->destColIndex = dest_col;
    move->sourceOriginalSymbol = game->gameBoard[source_row][source_col];
    move->destOriginalSymbol = game->gameBoard[dest_row][dest_col];
    return move;
}

void destroyGameMove(GAME_MOVE *move){
    if (move == NULL){
        return;
    }
    free(move);
}