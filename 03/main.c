#include <stdio.h>
#include "SPFIARGame.h"
#include "SPMiniMaxNode.h"
#include "SPMiniMax.h"

int main() {
    SPFiarGame *game = spFiarGameCreate(10);
    int *tops = game->tops;
    SPArrayList *gameStack = game->gameStack;
    printf("current player turn is: %c\n\n\n", game->currentPlayer);
    spFiarGameSetMove(game, 1);
    spFiarGameSetMove(game, 3);
    spFiarGameSetMove(game, 1);
    spFiarGameSetMove(game, 3);
    spFiarGameSetMove(game, 2);
    spFiarGameSetMove(game, 1);
    spFiarGameSetMove(game, 1);
    spFiarGameSetMove(game, 2);
    spFiarGameSetMove(game, 1);
    spFiarGameSetMove(game, 2);
    spFiarGameSetMove(game, 3);
    spFiarGameSetMove(game, 6);
    spFiarGameSetMove(game, 4);
    spFiarGameSetMove(game, 5);

    node *root = generateTree(game);

//    spFiarGamePrintBoard(game);
//    int *scoreHist = (int *)calloc(9, sizeof(int));
//    scoreHist += 4;
//    computeScoreHistogram(game->gameBoard, scoreHist);
//    printf("the address of score histogram is: %d\n", scoreHist);
//    for (int i = 0; i < 9; i++){
//        printf("scoreHist[%d] is on address %x and has value %d\n", -4+i, scoreHist-4 +i ,*(scoreHist -4 + i));
//    }
//    int score = calculateScoringFunction(scoreHist);
//    printf("the score of the board is: %d\n", score);
//    printf("scoreHist address %x\n", scoreHist);
//    scoreHist -= 4;
//    printf("scoreHist address %x\n", scoreHist);
//    free(scoreHist);
//    for (int i = 0; i < SP_FIAR_GAME_N_ROWS; i++) {
//        for (int j = 0; j < SP_FIAR_GAME_N_COLUMNS; j++) {
//            char val = game->gameBoard[i][j];
//            printf("val in position [%d,%d] is: %c\n", i, j, val);
//        }
//    }
//    printf("current player turn is: %c\n", game->currentPlayer);
//    for (int i =0; i < 7; i++){
//        printf("tops[%d] is: %d\n", i, *(tops + i));
//    }
//    for (int i = 0; i < gameStack->actualSize; i++){
//        printf("game stack at place %d value is: %d", i, gameStack->elements[i]);
//    }
//    spFiarGameUndoPrevMove(game);
//    for (int i = 0; i < SP_FIAR_GAME_N_ROWS; i++) {
//        for (int j = 0; j < SP_FIAR_GAME_N_COLUMNS; j++) {
//            char val = game->gameBoard[i][j];
//            printf("val in position [%d,%d] is: %c\n", i, j, val);
//        }
//    }
//    printf("current player turn is: %c\n", game->currentPlayer);
//    for (int i =0; i < 7; i++){
//        printf("tops[%d] is: %d\n", i, *(tops + i));
//    }
//    for (int i = 0; i < gameStack->actualSize; i++){
//        printf("game stack at place %d value is: %d\n", i, gameStack->elements[i]);
//    }
//    spFiarGamePrintBoard(game);
    return (0);
}
