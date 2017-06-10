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

    // Constant configuration flags
    int play = 1; // Program is live (set 0 to quit)
    int playCurrentGame = 0; // Still on current game (set 0 to restart)
    int shouldPrintBoard = 1; // Prompt the board for next step

    // Game loop
    while (play) {
        printf(ENTER_DIFFICULTY);
        int level = checkInitializationCommand();

        if (level == -99) break; // Error occurred while allocating memory
        if (level == -2) {
            printf(EXITING);
            break;
        }
        if (level == -1){
            printf(ERROR_INVALID_LEVEL);
            continue;
        }

        playCurrentGame = 1;
        SPFiarGame *game = spFiarGameCreate(20); // Create new game
        if (game == NULL)  break; // Memory allocation failed - exit the program

        // Current game loop
        while (playCurrentGame){

            // Check if board should be printed upon next move
            if (shouldPrintBoard) {
                spFiarGamePrintBoard(game);
                printf(MAKE_NEXT_MOVE);
                shouldPrintBoard = 0;
            }

            SPCommand cmd = parseUserCommand(); // Parse user command
            if (cmd.cmd == SP_ERROR) { // If error occurred while parsing the command (scanf)
                play = 0;
                spFiarGameDestroy(game);
                break;
            }

            // Command = "quit"
            if (cmd.cmd == SP_QUIT){
                play = 0;
                spFiarGameDestroy(game);
                printf(EXITING);
                break;
            }

            // Command = "restart_game"
            else if (cmd.cmd == SP_RESTART){
                spFiarGameDestroy(game);
                printf(RESTARTED);
                shouldPrintBoard = 1;
                break;
            }

            // Command is invalid
            else if (cmd.cmd == SP_INVALID_LINE){
                printf(ERROR_INVALID_COMMAND);
            }

            // Command is add_disc x
            else if (cmd.cmd == SP_ADD_DISC){

                // Check if x is a valid integer
                if (checkIfAddDiskCommandIsValid(cmd)){  // If x is of the right form
                    int columnToPlay = cmd.arg - 1; // 0-based

                    if (spFiarGameIsValidMove(game, columnToPlay)){ // If move is legal (i.e. column is not full and in range)

                        shouldPrintBoard = 1;
                        spFiarGameSetMove(game, columnToPlay); // Set the move on board
                        char winnerSymbolUserTurn = spFiarCheckWinner(game); // Update symbol

                        if (winnerSymbolUserTurn == -99) { // If error occurred while checking winner
                            play = 0;
                            spFiarGameDestroy(game);
                            break;
                        }

                        // Check if game is over after user move
                        if (winnerSymbolUserTurn != '\0'){ // -99 is the error conventions
                            handleGameOverScenario(winnerSymbolUserTurn, game);
                            playCurrentGame = 0;
                            break;
                        }

                        // Handle computer turn using MiniMax algorithm
                        int computerPlayColumn;
                        computerPlayColumn = spMinimaxSuggestMove(game, level);

                        if (computerPlayColumn == -99) { // Error occurred in MiniMax algorithm
                            play = 0;
                            spFiarGameDestroy(game);
                            break;
                        }

                        printf(COMPUTER_MOVE, computerPlayColumn+1);
                        spFiarGameSetMove(game, computerPlayColumn);

                        // Check if game is over after computer move
                        char winnerSymbolCompTurn = spFiarCheckWinner(game);

                        if (winnerSymbolCompTurn == -99) {
                            play = 0;
                            spFiarGameDestroy(game);
                            break;
                        }

                        if (winnerSymbolCompTurn != '\0'){ // 0 is returned when no winner detected
                            handleGameOverScenario(winnerSymbolCompTurn, game);
                            playCurrentGame = 0;
                            break;
                        }
                    }

                    // If move is illegal
                    else {
                        printf(ERROR_COLUMN_FULL, columnToPlay+1);
                    }
                }

                // If move is off-range
                else {
                    printf(ERROR_COLUMN_RANGE);
                }

            // If command = "suggest_move"
            } else if(cmd.cmd == SP_SUGGEST_MOVE){
                int suggestedColumnMove = spMinimaxSuggestMove(game, level);

                if (suggestedColumnMove == -99) {
                    play = 0;
                    spFiarGameDestroy(game);
                    break;
                }

                printf(SUGGESTED_MOVE, suggestedColumnMove+1);
            }

            // If command = "undo_move"
            else if (cmd.cmd == SP_UNDO_MOVE){
                performUndoMoveActions(game, &shouldPrintBoard);
            }
        }

        // If current game is restarted
        if (playCurrentGame == 0){
            while (true) { // Only allow quit and restart_game

                SPCommand endGameCommand = parseUserCommand();
                if (endGameCommand.cmd == SP_ERROR) { // If error occurred while parsing the command (scanf)
                    play = 0;
                    spFiarGameDestroy(game);
                    break;
                }

                // If command = "quit"
                if (endGameCommand.cmd == SP_QUIT){
                    printf(EXITING);
                    spFiarGameDestroy(game);
                    play = 0;
                    break;
                }

                // If command = "restart_game"
                else if (endGameCommand.cmd == SP_RESTART){
                    printf(RESTARTED);
                    spFiarGameDestroy(game);
                    shouldPrintBoard = 1;
                    break;
                }

                // Command is invalid
                else if (endGameCommand.cmd == SP_INVALID_LINE){
                    printf(ERROR_INVALID_COMMAND);
                }

                // Any other command is illegal
                else {
                    printf(ERROR_GAME_OVER);
                }
            }
        }
    }

    return (0);
}


