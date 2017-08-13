#include <stdio.h>
#include "MatchManagement.h"
#include "MovesStack.h"
#include "CommandParsing.h"
#include "XMLParser.h"

int main() {
    CHESS_MATCH *match = createNewChessMatch();
    initGameBoard(match->game);
    printChessGameBoard(match->game);
    char *matchStr;
    printf("\n");
    matchStr = transformMatchToXMLString(match);
    printf("the representation is:\n%s", matchStr);
    writeXMLStringToFile(matchStr, "C:\\Users\\oklainfeld\\Downloads\\chess_match.xml");
}

