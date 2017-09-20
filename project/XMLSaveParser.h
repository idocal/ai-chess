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

/**
 * an interface for writing a match object content into a given file in an xml format
 * @param match
 * @param addressToFile
 * @return
 * 0 on success
 * -1 on failure
 */

int writeMatchObjectToXmlFile(CHESS_MATCH *match, char *addressToFile);

/**
 * writes a given pre allocated string into a desired file
 * @param xmlString
 * @param addressToFile
 * @return
 * 0 if the whole string was written to the file successfully
 * -1 if some error occurred
 */

int writeXMLStringToFile(char *xmlString, char* addressToFile);

/**
 * encoding a given match object into a string encoded as an xml file
 * @param match
 * @return a string encoding the match object in an xml format
 */

char *transformMatchToXMLString(CHESS_MATCH *match);

/**
 * writes to the given file an xml tag line,
 * matching to the desired tag name supplied
 * @param fileStr
 * @param tagName
 * @param match
 */


void concatSettingTag(char *fileStr, char *tagName, CHESS_MATCH *match);

/**
 * writes to the given file the game board content encapsulated in <board> tag
 * @param fileStr
 * @param game
 */

void concatBoardTag(char *fileStr, CHESS_GAME *game);

/**
 * extracts a desired argument from a match object
 * @param paramDescription
 * @param match
 * @return
 * the desired argument (user color, current turn, game mode, difficulty)
 * or -1 if the given description doesn't match any match argument
 */

char getSettingParameterValue(char *paramDescription, CHESS_MATCH *match);

/**
 * appends the given char to the end of a given string
 * (assuming the pre allocated string has enough space for the addition)
 * @param destStr
 * @param c
 */

void appendCharToStringEnd(char *destStr, char c);

/**
 * convert a single digit to the ASCII character which represents it
 * @param digit
 * @return char with an appropriate ASCII value to represent the integer number as a char on the screen
 */

char transformDigitIntToChar(int digit);


#endif //PROJECT_XMLPARSER_H
