//
// Created by okleinfeld on 8/12/2017.
//

#ifndef PROJECT_XMLPARSER_H
#define PROJECT_XMLPARSER_H

#include <stdio.h>
#include <string.h>
#include "MatchManagement.h"
#include <assert.h>

#define MAX_FILE_SIZE 2048

void writeMatchObjectToXmlFile(CHESS_MATCH *match, char *addressToFile);

int writeXMLStringToFile(char *xmlString, char* addressToFile);

char *transformMatchToXMLString(CHESS_MATCH *match);

void concatSettingTag(char *fileStr, char *tagName, CHESS_MATCH *match);

void concatBoardTag(char *fileStr, CHESS_GAME *game);

char getSettingParameterValue(char *paramDescription, CHESS_MATCH *match);

void appendCharToStringEnd(char *destStr, char c);

char transformDigitIntToChar(int digit);


#endif //PROJECT_XMLPARSER_H
