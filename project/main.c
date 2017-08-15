#include <stdio.h>
#include "MatchManagement.h"
#include "MovesStack.h"
#include "CommandParsing.h"
#include "XMLSaveParser.h"
#include "Matrix.h"
#include "GameAux.h"
#include "XMLLoadParser.h"

int main() {
//    CHESS_MATCH *match = createNewChessMatch();
//    initGameBoard(match->game);
//    printChessGameBoard(match->game);
//    char *matchStr;
//    printf("\n");
//    matchStr = transformMatchToXMLString(match);
//    printf("the representation is:\n%s", matchStr);
//    writeXMLStringToFile(matchStr, "C:\\Users\\oklainfeld\\Downloads\\chess_match.xml");

//    CHESS_GAME *game = createEmptyGame();
//    initGameBoard(game);
//    printChessGameBoard(game);
//    printf("\n");
//
//    GAME_MOVE *newMove = createGameMove(game, 1, 3, 5, 3);
//
//    performMove(game,newMove);
//
//    printChessGameBoard(game);

    FILE *fp = fopen("C:\\Users\\oklainfeld\\Downloads\\chess_match.xml", "r");
    char * buffer = malloc(sizeof(char) * MAX_LINE_LENGTH);
    readLineFromFileIntoBuffer(fp, buffer);
    printf("%s\n", buffer);
    readLineFromFileIntoBuffer(fp, buffer);
    printf("%s\n", buffer);
    readLineFromFileIntoBuffer(fp, buffer);
    printf("%s\n", buffer);
    XMLTagObject *tag = parseXmlLineToTagObject(buffer);
    printf("the tag value is %d\n", tag->tagValue);
    readLineFromFileIntoBuffer(fp, buffer);
    printf("%s\n", buffer);
    XMLTagObject *tag2 = parseXmlLineToTagObject(buffer);
    printf("the tag value is %d\n", tag2->tagValue);
    readLineFromFileIntoBuffer(fp, buffer);
    printf("%s\n", buffer);
    XMLTagObject *tag3 = parseXmlLineToTagObject(buffer);
    printf("the tag value is %d\n", tag3->tagValue);

}

