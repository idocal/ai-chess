#ifndef SPMAINAUX_H_
#define SPMAINAUX_H_

#include "SPFAIRParser.h"
#include "SPFIARGame.h"
#include <stdio.h>
#include <stdlib.h>
//put auxiliary functions and constants used by the main function here.

int checkInitializationCommand();

int checkIfAddDiskCommandIsValid(SPCommand cmd);

SPCommand parseUserCommand();

void handleGameOverScenario(char winnerSymbol, SPFiarGame *game);

int getLastColumnPlayed(SPFiarGame *game);

void performUndoMoveActions(SPFiarGame *game);

#endif
