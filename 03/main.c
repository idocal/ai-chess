#include <stdio.h>
#include "SPFIARGame.h"
#include "SPMiniMax.h"
#include "SPMainAux.h"

#define ENTER_DIFFICULTY "Please enter the difficulty level between [1-7]:\n"
#define EXITING "Exiting...\n"
#define ERROR_INVALID_LEVEL "Error: invalid level (should be between 1 to 7)\n"
#define MAKE_NEXT_MOVE "Please make the next move:\n"
#define RESTARTED "Game restarted!\n"
#define ERROR_INVALID_COMMAND "Error: invalid command\n"
#define COMPUTER_MOVE "Computer move: add disc to column %d\n"
#define ERROR_COLUMN_FULL "Error: column %d is full\n"
#define ERROR_COLUMN_RANGE "Error: column number must be in range 1-7\n"
#define SUGGESTED_MOVE "Suggested move: drop a disc to column %d\n"
#define ERROR_GAME_OVER "Error: the game is over\n"


int main() {
    int play = 1;
    int playCurrentGame = 0;
    int shouldPrintBoard = 1;
    while (play) {
        printf(ENTER_DIFFICULTY);
        int level = checkInitializationCommand();
        if (level == -2) {
            printf(EXITING);
            break;
        }
        if (level == -1){
            printf(ERROR_INVALID_LEVEL);
            continue;
        }
        playCurrentGame = 1;
        SPFiarGame *game = spFiarGameCreate(20);
        while (playCurrentGame){
            if (shouldPrintBoard) {
                spFiarGamePrintBoard(game);
                printf(MAKE_NEXT_MOVE);
                shouldPrintBoard = 0;
            }
            SPCommand cmd = parseUserCommand();
            if (cmd.cmd == SP_QUIT){
                play = 0;
                spFiarGameDestroy(game);
                printf(EXITING);
                break;
            } else if (cmd.cmd == SP_RESTART){
                spFiarGameDestroy(game);
                printf(RESTARTED);
                shouldPrintBoard = 1;
                break;
            } else if (cmd.cmd == SP_INVALID_LINE){
                printf(ERROR_INVALID_COMMAND);
            } else if (cmd.cmd == SP_ADD_DISC){
                if (checkIfAddDiskCommandIsValid(cmd)){
                    int columnToPlay = cmd.arg - 1;
                    if (spFiarGameIsValidMove(game, columnToPlay)){
                        shouldPrintBoard = 1;
                        spFiarGameSetMove(game, columnToPlay);
                        char winnerSymbolUserTurn = spFiarCheckWinner(game);
                        if (winnerSymbolUserTurn != -99 && winnerSymbolUserTurn != '\0'){
                            handleGameOverScenario(winnerSymbolUserTurn, game);
                            playCurrentGame = 0;
                            break;
                        }
                        int computerPlayColumn;
                        computerPlayColumn = spMinimaxSuggestMove(game, level);
                        printf(COMPUTER_MOVE, computerPlayColumn+1);
                        spFiarGameSetMove(game, computerPlayColumn);
                        char winnerSymbolCompTurn = spFiarCheckWinner(game);
                        if (winnerSymbolCompTurn != -99 && winnerSymbolCompTurn != '\0'){
                            handleGameOverScenario(winnerSymbolCompTurn, game);
                            playCurrentGame = 0;
                            break;
                        }
                    }
                    else{
                        printf(ERROR_COLUMN_FULL, columnToPlay+1);
                    }
                }
                else{
                    printf(ERROR_COLUMN_RANGE);
                }
            } else if(cmd.cmd == SP_SUGGEST_MOVE){
                int suggestedColumnMove = spMinimaxSuggestMove(game, level);
                printf(SUGGESTED_MOVE, suggestedColumnMove+1);
            } else if (cmd.cmd == SP_UNDO_MOVE){
                performUndoMoveActions(game, &shouldPrintBoard);
            }
        }
        if (playCurrentGame == 0){
            while (true) {
                SPCommand endGameCommand = parseUserCommand();
                if (endGameCommand.cmd == SP_QUIT){
                    printf(EXITING);
                    spFiarGameDestroy(game);
                    play = 0;
                    break;
                } else if (endGameCommand.cmd == SP_RESTART){
                    printf(RESTARTED);
                    spFiarGameDestroy(game);
                    shouldPrintBoard = 1;
                    break;
                } else {
                    printf(ERROR_GAME_OVER);
                }
            }
        }
    }

    return (0);
}
