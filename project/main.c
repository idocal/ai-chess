#include <stdio.h>
#include "MatchManagement.h"
#include "MovesStack.h"
#include "CommandParsing.h"
#include "XMLParser.h"
#include "Matrix.h"
#include "GameAux.h"
#include "PieceRules.h"

int main() {
//    CHESS_MATCH *match = createNewChessMatch();
//    initGameBoard(match->game);
//    printChessGameBoard(match->game);
//    char *matchStr;
//    printf("\n");
//    matchStr = transformMatchToXMLString(match);
//    printf("the representation is:\n%s", matchStr);
//    writeXMLStringToFile(matchStr, "C:\\Users\\oklainfeld\\Downloads\\chess_match.xml");

    CHESS_GAME *game = createEmptyGame();
    initGameBoard(game);
    GAME_MOVE *move = createGameMove(game, 7, 3, 3, 7);
    performMove(game, move);
    destroyGameMove(move);
    printChessGameBoard(game);
    printf("\n\n");
//
//    move = createGameMove(game, 1, 5, 2, 5);
//    performMove(game, move);
//    destroyGameMove(move);
//    printChessGameBoard(game);
//    printf("\n\n");


    MATRIX *moves = pawnPossibleMoves(game, 1, 3, 1, true);
    matPrint(moves, 0);
    matDestroy(moves);
}

