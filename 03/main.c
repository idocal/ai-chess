#include <stdio.h>
#include "SPFIARGame.h"
#include "SPMiniMaxNode.h"
#include "SPMiniMax.h"
#include "SPMainAux.h"

int main() {
    int play = 1;
    int playCurrentGame = 0;
    while (play) {
        printf("Please enter the difficulty level between [1-7]:\n");
        int level = checkInitializationCommand();
        if (level == -2) {
            printf("Exiting...\n");
            break;
        }
        if (level == -1){
            printf("Error: invalid level (should be between 1 to 7\n");
            continue;
        }
        playCurrentGame = 1;
        SPFiarGame *game = spFiarGameCreate(20);
        while (playCurrentGame){
            spFiarGamePrintBoard(game);
            printf("Please make the next move:\n");
            SPCommand cmd = parseUserCommand();
            if (cmd.cmd == SP_QUIT){
                play = 0;
                spFiarGameDestroy(game);
                printf("Exiting...\n");
                break;
            } else if (cmd.cmd == SP_RESTART){
                spFiarGameDestroy(game);
                printf("Game restarted!\n");
                break;
            } else if (cmd.cmd == SP_INVALID_LINE){
                printf("Error: invalid command\n");
            } else if (cmd.cmd == SP_ADD_DISC){
                if (checkIfAddDiskCommandIsValid(cmd)){
                    int columnToPlay = cmd.arg - 1;
                    if (spFiarGameIsValidMove(game, columnToPlay)){
                        spFiarGameSetMove(game, columnToPlay);
                        char winnerSymbolUserTurn = spFiarCheckWinner(game);
                        if (winnerSymbolUserTurn != NULL){
                            handleGameOverScenario(winnerSymbolUserTurn, game);
                            playCurrentGame = 0;
                            break;
                        }
                        int computerPlayColumn;
                        computerPlayColumn = spMinimaxSuggestMove(game, level);
                        printf("Computer move: add disc to column %d\n", computerPlayColumn+1);
                        spFiarGameSetMove(game, computerPlayColumn);
                        char winnerSymbolCompTurn = spFiarCheckWinner(game);
                        if (winnerSymbolCompTurn != NULL){
                            handleGameOverScenario(winnerSymbolCompTurn, game);
                            playCurrentGame = 0;
                            break;
                        }
                    }
                    else{
                        printf("Error: column %d is full\n", columnToPlay+1);
                    }
                }
                else{
                    printf("Error: column number must be in range 1-7\n");
                }
            } else if(cmd.cmd == SP_SUGGEST_MOVE){
                int suggestedColumnMove = spMinimaxSuggestMove(game, level);
                printf("Suggested move: drop a disc to column %d\n", suggestedColumnMove+1);
            } else if (cmd.cmd == SP_UNDO_MOVE){
                performUndoMoveActions(game);
            }
        }
        if (playCurrentGame == 0){
            while (true) {
                SPCommand endGameCommand = parseUserCommand();
                if (endGameCommand.cmd == SP_QUIT){
                    printf("Exiting...\n");
                    spFiarGameDestroy(game);
                    play = 0;
                    break;
                } else if (endGameCommand.cmd == SP_RESTART){
                    printf("Game restarted!\n");
                    spFiarGameDestroy(game);
                    break;
                } else if (endGameCommand.cmd == SP_UNDO_MOVE){
                    performUndoMoveActions(game);
                    spFiarGamePrintBoard(game);
                } else{
                    printf("Error: the game is over\n");
                }
            }
        }
    }
//    int level = checkInitializationCommand();
//    if (level == -1){
//        printf("Error: invalid level (should be between 1 to 7\n");
//    }
//    printf("level is: %d\n", level);
//    SPFiarGame *game = spFiarGameCreate(10);
//    int *tops = game->tops;
//    SPArrayList *gameStack = game->gameStack;
//    printf("current player turn is: %c\n\n\n", game->currentPlayer);
//    spFiarGameSetMove(game, 1);
//    spFiarGameSetMove(game, 3);
//    spFiarGameSetMove(game, 1);
//    spFiarGameSetMove(game, 3);
//    spFiarGameSetMove(game, 2);
//    spFiarGameSetMove(game, 1);
//    spFiarGameSetMove(game, 1);
//    spFiarGameSetMove(game, 2);
//    spFiarGameSetMove(game, 1);
//    spFiarGameSetMove(game, 2);
//    spFiarGameSetMove(game, 3);
//    spFiarGameSetMove(game, 6);
//    spFiarGameSetMove(game, 4);
//    spFiarGameSetMove(game, 5);
//    spFiarGamePrintBoard(game);
//
//    int move = spMinimaxSuggestMove(game, 7);
//    printf("suggested move is: %d\n\n", move);
//    spFiarGameSetMove(game, move);
//    spFiarGamePrintBoard(game);
//    int move2 = spMinimaxSuggestMove(game, 7);
//    printf("suggested move is: %d\n\n", move2);
//    spFiarGameSetMove(game, move2);
//    spFiarGamePrintBoard(game);
//    int move3 = spMinimaxSuggestMove(game, 7);
//    printf("suggested move is: %d\n\n", move3);
//    spFiarGameSetMove(game, move3);
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
