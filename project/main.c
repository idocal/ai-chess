#include <stdio.h>
#include "MatchManagement.h"
#include "MovesStack.h"
#include "CommandParsing.h"
#include "XMLSaveParser.h"
#include "Matrix.h"
#include "GameAux.h"
#include "XMLLoadParser.h"
#include "PieceRules.h"

#define WELCOME_MESSAGE "Specify game setting or type 'start' to begin a game with the current setting:\n"

int main() {
    printf(WELCOME_MESSAGE);
    CHESS_MATCH *match = createNewChessMatch();
    if (match == NULL){
        return 0;
    }

    // Match settings state loop
    bool initGame = initiateChessMatch(&match);
    if (initGame == false){
        destroyChessMatch(match);
        return 0;
    }

    // Game state
    initiateChessGame(match);
}


