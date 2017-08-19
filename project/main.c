#include <stdio.h>
#include "MatchManagement.h"
#include "MovesStack.h"
#include "CommandParsing.h"
#include "XMLSaveParser.h"
#include "Matrix.h"
#include "GameAux.h"
#include "XMLLoadParser.h"
#include "PieceRules.h"

int main() {
    printf("Specify game setting or type 'start' to begin a game with the current setting:\n");
    CHESS_MATCH *match = createNewChessMatch();
    if (match == NULL){
        return 0;
    }
    bool initGame = initiateChessGame(match);
    if (initGame == false){
        destroyChessMatch(match);
        return 0;
    }
    printf("The Game has initiated\n");
    printChessGameBoard(match->game);
}


