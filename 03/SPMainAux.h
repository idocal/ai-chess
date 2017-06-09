#ifndef SPMAINAUX_H_
#define SPMAINAUX_H_

#include "SPFIARParser.h"
#include "SPFIARGame.h"
#include <stdio.h>
#include <stdlib.h>

#define GAME_OVER_WIN "Game over: you win\nPlease enter 'quit' to exit or 'restart' to start a new game!\n"
#define GAME_OVER_LOSE "Game over: computer wins\nPlease enter 'quit' to exit or 'restart' to start a new game!\n"
#define GAME_OVER_TIE "Game over: it's a tie\nPlease enter 'quit' to exit or 'restart' to start a new game!\n"
#define ERROR_CANNOT_UNDO "Error: cannot undo previous move!\n"
#define REMOVE_COMPUTER_DISC "Remove disc: remove computer's disc at column %d\n"
#define REMOVE_USER_DISC "Remove disc: remove user's disc at column %d\n"

/**
 * This function is called in the difficulty choice stage.
 * It detects only integers in range 1-7.
 *
 * @return
 * -2 If the command is "quit"
 * -1 If the command is illegal (i.e. not an integer in range 1-7)
 */
int checkInitializationCommand();

/**
 * Checks if "add_disc" command is of the form:
 * "add_disc x" and x is an integer in range 1-7
 *
 * @param cmd - the command in SPCommand struct.
 * @return
 * 1 If add_disc is of the right form
 * 0 elsewise
 */
int checkIfAddDiskCommandIsValid(SPCommand cmd);

/**
 * Receive the command from standard input,
 * Parse it using the function spParserPraseLine in SPFIARParser.c
 *
 * @return
 * The command in SPCommand struct.
 */
SPCommand parseUserCommand();

/**
 * In each move we check rather the game is over.
 * For game over there are 3 scenarios: win, lose or tie.
 * This function only prints the result to the screen.
 *
 * @param winnerSymbol - The symbol of the winner
 * @param game
 */
void handleGameOverScenario(char winnerSymbol, SPFiarGame *game);

/**
 * Returns the column played on previous move.
 * This is useful for the "undo_move" logic.
 *
 *
 * @param game - A pointer to the game struct.
 * @return
 * -1 If no moves have been set before.
 * int lastColumnPlayed in range 1-7.
 */
int getLastColumnPlayed(SPFiarGame *game);

/**
 * Performs the "undo_move" command.
 * Go back 2 steps in game stack using the function spFiarGameUndoPrevMove in SPFIARGame.c
 *
 * @param game - A pointer to the game struct.
 * @param shouldPrintBoardPointer
 */
void performUndoMoveActions(SPFiarGame *game, int *shouldPrintBoardPointer);

#endif
