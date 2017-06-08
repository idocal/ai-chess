//
// Created by okleinfeld on 5/20/2017.
//

#include "SPFIARGame.h"
#include <stdio.h>
#include <limits.h>

SPFiarGame* spFiarGameCreate(int historySize){
    SPFiarGame *game = (SPFiarGame *) malloc(sizeof(SPFiarGame));
    if (game == NULL || historySize <= 0){
        return NULL;
    }
    game->gameStack = spArrayListCreate(historySize);
    if (game->gameStack == NULL){
        free(game);
        return NULL;
    }
    for (int i = 0; i < SP_FIAR_GAME_N_ROWS; i++){
        for (int j = 0; j < SP_FIAR_GAME_N_COLUMNS; j++){
            game->gameBoard[i][j] = SP_FIAR_GAME_EMPTY_ENTRY;
        }
    }
    for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++){
        game->tops[i] = 0;
    }
    game->currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;
    return game;
}

SPFiarGame* spFiarGameCopy(SPFiarGame* src){
    if (src == NULL){
        return NULL;
    }
    SPFiarGame *cpyGame = (SPFiarGame *) malloc(sizeof(SPFiarGame));
    if (cpyGame == NULL){
        return NULL;
    }
    cpyGame->gameStack = spArrayListCreate(src->gameStack->maxSize);
    if (cpyGame->gameStack == NULL){
        free(cpyGame);
        return NULL;
    }
    for (int i = 0; i < SP_FIAR_GAME_N_ROWS; i++){
        for (int j = 0; j < SP_FIAR_GAME_N_COLUMNS; j++){
            cpyGame->gameBoard[i][j] = src->gameBoard[i][j];
        }
    }
    for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++){
        cpyGame->tops[i] = src->tops[i];
    }
    cpyGame->currentPlayer = src->currentPlayer;
    return cpyGame;
}

void spFiarGameDestroy(SPFiarGame* src){
    if (src == NULL){
        return;
    }
    free(src->gameStack);
    free(src);
}

void switchPlayer(SPFiarGame *src){
    if (src == NULL){
        return;
    }
    if (src->currentPlayer == SP_FIAR_GAME_PLAYER_1_SYMBOL){
        src->currentPlayer = SP_FIAR_GAME_PLAYER_2_SYMBOL;
    }
    else {
        src->currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;
    }
}

SP_FIAR_GAME_MESSAGE spFiarGameSetMove(SPFiarGame* src, int col){
    if (src == NULL || col < 0 || col > SP_FIAR_GAME_N_COLUMNS -1){
        return SP_FIAR_GAME_INVALID_ARGUMENT;
    }
    int rowTop = src->tops[col];
    if (rowTop == SP_FIAR_GAME_N_ROWS){
        return SP_FIAR_GAME_INVALID_MOVE;
    }
    src->gameBoard[rowTop][col] = src->currentPlayer;
    src->tops[col] += 1;
    if (spArrayListIsFull(src->gameStack) == true){
        spArrayListRemoveFirst(src->gameStack);
        spArrayListAddLast(src->gameStack, col);
    }
    else{
        spArrayListAddLast(src->gameStack, col);
    }
    switchPlayer(src);
    return SP_FIAR_GAME_SUCCESS;
}

bool spFiarGameIsValidMove(SPFiarGame* src, int col){
    if (src == NULL){
        return NULL;
    }
    int *tops = src->tops;
    if (tops[col] == SP_FIAR_GAME_N_ROWS){
        return false;
    }
    else{
        return true;
    }
}

SP_FIAR_GAME_MESSAGE spFiarGameUndoPrevMove(SPFiarGame* src){
    if (src == NULL){
        return SP_FIAR_GAME_INVALID_ARGUMENT;
    }
    SPArrayList *gameStack = src->gameStack;
    int *tops = src->tops;
    if (spArrayListIsEmpty(gameStack) == true){
        return SP_FIAR_GAME_NO_HISTORY;
    }
    int lastColumnPlayed = spArrayListGetLast(gameStack);
    int i = tops[lastColumnPlayed] -1;
    int j = lastColumnPlayed;
    src->gameBoard[i][j] = SP_FIAR_GAME_EMPTY_ENTRY;
    tops[lastColumnPlayed] -= 1;
    spArrayListRemoveLast(gameStack);
    switchPlayer(src);
    return SP_FIAR_GAME_SUCCESS;
}

SP_FIAR_GAME_MESSAGE spFiarGamePrintBoard(SPFiarGame* src){
    if (src == NULL){
        return SP_FIAR_GAME_INVALID_ARGUMENT;
    }
    for (int i = SP_FIAR_GAME_N_ROWS-1; i >=0; i--){
        printf("%c", '|');
        for (int j = 0; j < SP_FIAR_GAME_N_COLUMNS; j++){
            printf(" %c", src->gameBoard[i][j]);
        }
        printf(" |\n");
    }
    for (int i = 0; i < 17; i++){
        printf("%c", '-');
    }
    printf("\n%c", ' ');
    int counter = 1;
    for (int i = 0; i < 7; i++){
        printf(" %d", counter);
        counter++;
    }
    printf("  \n");
    return SP_FIAR_GAME_SUCCESS;
}

char spFiarGameGetCurrentPlayer(SPFiarGame* src){
    if (src == NULL){
        return -99;
    }
    else{
        return src->currentPlayer;
    }
}

int *computeScoreHistogram(SPFiarGame *game, int *scoreHist){
    if (game == NULL || scoreHist == NULL){
        return NULL;
    }
    calculateRowSpans(game->gameBoard, scoreHist);
    calculateColumnsSpans(game->gameBoard, scoreHist);
    calculateCRightCrossSpans(game->gameBoard, scoreHist);
    calculateCLeftCrossSpans(game->gameBoard, scoreHist);
    return scoreHist;
}


void calculateRowSpans(char gameBoard[SP_FIAR_GAME_N_ROWS][SP_FIAR_GAME_N_COLUMNS], int *Histogram){
    if (gameBoard == NULL || Histogram == NULL){
        return;
    }
    for (int k = 0; k < SP_FIAR_GAME_N_ROWS; k++){
        for (int i = 0; i < 4; i++){
            int spanScore = 0;
            for (int j = i; j < i+4; j++){
                if (gameBoard[k][j] == SP_FIAR_GAME_PLAYER_1_SYMBOL){
                    spanScore += 1;
                }
                if (gameBoard[k][j] == SP_FIAR_GAME_PLAYER_2_SYMBOL){
                    spanScore -= 1;
                }
            }
            *(Histogram + spanScore) += 1;
        }
    }
}

void calculateColumnsSpans(char gameBoard[SP_FIAR_GAME_N_ROWS][SP_FIAR_GAME_N_COLUMNS], int *Histogram){
    if (gameBoard == NULL || Histogram == NULL){
        return;
    }
    for (int k = 0; k < SP_FIAR_GAME_N_COLUMNS; k++){
        for (int i = 0; i < 3; i++){
            int spanScore = 0;
            for (int j = i; j < i+4; j++){
                if (gameBoard[j][k] == SP_FIAR_GAME_PLAYER_1_SYMBOL){
                    spanScore += 1;
                }
                if (gameBoard[j][k] == SP_FIAR_GAME_PLAYER_2_SYMBOL){
                    spanScore -= 1;
                }
            }
            *(Histogram + spanScore) += 1;
        }
    }
}

void calculateCRightCrossSpans(char gameBoard[SP_FIAR_GAME_N_ROWS][SP_FIAR_GAME_N_COLUMNS], int *Histogram){
    if (gameBoard == NULL || Histogram == NULL){
        return;
    }
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3- i; j++){
            int spanScore = 0;
            for (int k = 0; k < 4; k++){
                if (gameBoard[i+j+k][j+k] == SP_FIAR_GAME_PLAYER_1_SYMBOL){
                    spanScore += 1;
                }
                if (gameBoard[i+j+k][j+k] == SP_FIAR_GAME_PLAYER_2_SYMBOL){
                    spanScore -= 1;
                }
            }
            *(Histogram + spanScore) += 1;
        }
    }
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3- i; j++){
            int spanScore = 0;
            for (int k = 0; k < 4; k++){
                if (gameBoard[j+k][i+j+k+1] == SP_FIAR_GAME_PLAYER_1_SYMBOL){
                    spanScore += 1;
                }
                if (gameBoard[j+k][i+j+k+1] == SP_FIAR_GAME_PLAYER_2_SYMBOL){
                    spanScore -= 1;
                }
            }
            *(Histogram + spanScore) += 1;
        }
    }
}

void calculateCLeftCrossSpans(char gameBoard[SP_FIAR_GAME_N_ROWS][SP_FIAR_GAME_N_COLUMNS], int *Histogram){
    if (gameBoard == NULL || Histogram == NULL){
        return;
    }
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3- i; j++){
            int spanScore = 0;
            for (int k = 0; k < 4; k++){
                if (gameBoard[5-i-j-k][j+k] == SP_FIAR_GAME_PLAYER_1_SYMBOL){
                    spanScore += 1;
                }
                if (gameBoard[5-i-j-k][j+k] == SP_FIAR_GAME_PLAYER_2_SYMBOL){
                    spanScore -= 1;
                }
            }
            *(Histogram + spanScore) += 1;
        }
    }
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3- i; j++){
            int spanScore = 0;
            for (int k = 0; k < 4; k++){
                if (gameBoard[5-j-k][j+k+i+1] == SP_FIAR_GAME_PLAYER_1_SYMBOL){
                    spanScore += 1;
                }
                if (gameBoard[5-j-k][j+k+i+1] == SP_FIAR_GAME_PLAYER_2_SYMBOL){
                    spanScore -= 1;
                }
            }
            *(Histogram + spanScore) += 1;
        }
    }
}

char spFiarCheckWinner(SPFiarGame* src){
    if (src == NULL){
        return -99;
    }
    int *gameHistogram = (int *) calloc(9, sizeof(int));
    if (gameHistogram == NULL){
        return -99;
    }
    gameHistogram += 4;
    gameHistogram = computeScoreHistogram(src, gameHistogram);
    if (*(gameHistogram - 4) >= 1){
        free(gameHistogram-4);
        return SP_FIAR_GAME_PLAYER_2_SYMBOL;
    }
    if (*(gameHistogram + 4) >= 1){
        free(gameHistogram-4);
        return SP_FIAR_GAME_PLAYER_1_SYMBOL;
    }
    int gameOverTie = 1;
    for (int i = 0; i < SP_FIAR_GAME_N_ROWS; i++){
        for (int j = 0; j < SP_FIAR_GAME_N_COLUMNS; j++){
            if (src->gameBoard[i][j] == SP_FIAR_GAME_EMPTY_ENTRY){
                gameOverTie = 0;
                break;
            }
        }
    }

    if (gameOverTie){
        free(gameHistogram-4);
        return SP_FIAR_GAME_TIE_SYMBOL;
    }
    free(gameHistogram-4);
    return '\0';
}

int calculateScoringFunction(int *scoreHistogram){
    if (scoreHistogram == NULL){
        return -99;
    }
    if (*(scoreHistogram -4) > 0){
        return INT_MIN;
    }
    if (*(scoreHistogram +4) > 0){
        return INT_MAX;
    }
    int weightVector[] = {-5, -2, -1, 0, 1, 2, 5};
    int score = 0;
    for (int i = 0; i < 7; i++){
        score += *(scoreHistogram -3 + i) * weightVector[i];
    }
    return score;
}
