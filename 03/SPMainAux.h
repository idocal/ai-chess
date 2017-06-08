#ifndef SPMAINAUX_H_
#define SPMAINAUX_H_

#include "SPFAIRParser.h"
#include "SPFIARGame.h"
#include <stdio.h>
#include <stdlib.h>
//put auxiliary functions and constants used by the main function here.

#define GAME_OVER_WIN "Game over: you win\nPlease enter 'quit' to exit or 'restart' to start a new game!\n"
#define GAME_OVER_LOSE "Game over: computer wins\nPlease enter 'quit' to exit or 'restart' to start a new game!\n"
#define GAME_OVER_TIE "Game over: it's a tie\nPlease enter 'quit' to exit or 'restart' to start a new game!\n"
#define ERROR_CANNOT_UNDO "Error: cannot undo previous move!\n"
#define REMOVE_COMPUTER_DISC "Remove disc: remove computer's disc at column %d\n"
#define REMOVE_USER_DISC "Remove disc: remove user's disc at column %d\n"

int checkInitializationCommand();

int checkIfAddDiskCommandIsValid(SPCommand cmd);

SPCommand parseUserCommand();

void handleGameOverScenario(char winnerSymbol, SPFiarGame *game);

int getLastColumnPlayed(SPFiarGame *game);

void performUndoMoveActions(SPFiarGame *game, int *shouldPrintBoardPointer);

#endif
