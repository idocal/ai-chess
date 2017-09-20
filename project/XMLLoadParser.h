//
// Created by okleinfeld on 8/15/2017.
//

#ifndef PROJECT_XMLLOADPARSER_H
#define PROJECT_XMLLOADPARSER_H

#include "MatchManagement.h"
#include "XMLSaveParser.h"
#include <string.h>

#define MAX_LINE_LENGTH 1024

/**
 * an enum to represent the possible game setting XML tags names
 * the game board content is represented differently
 */

typedef enum xml_tag {
    CURRENT_TURN_TAG,
    GAME_MODE_TAG,
    DIFFICULTY_TAG,
    USER_COLOR_TAG,
    INVALID_TAG_NAME
} XmlTag;

/**
 * an object which represent an xml tag in an xml file
 * the object contains the enum of the tag name and the integer value of the tag
 */

typedef struct xml_tag_object {
    XmlTag tagName;
    int tagValue;
} XMLTagObject;

/**
 * this is the interface which is used to crate a match object from an xml file representing a match
 * @param fileAddress
 * @return a Chess Match object which contains data parsed from the xml file
 */


CHESS_MATCH* parseXMLGameFile(char *fileAddress);


/**
 * the functions parses the current line from the given file,
 * saving the line content into a pre allocated string (assuming pre allocated buffer is big enough)
 * @param fp
 * @param buffer
 */

void readLineFromFileIntoBuffer(FILE *fp, char* buffer);

/**
 * the function transforms a string containing a tag name into an xml tag enum
 * @param tagName
 * @return an XML tag enum with the matching tag name or INVALID_TAG_NAME in case of an invalid tag
 */

XmlTag parseTagNameStringToEnum(char* tagName);

/**
 * the function parses a given line from an xml file (setting argument line not the board part)
 * returning a matching xml tag object by combining the functions from above
 * @param line
 * @return an xml tag object containing the tag name and integer value
 */

XMLTagObject* parseXmlLineToTagObject(char* line);

/**
 * a destructor for the xml tag object
 * @param tagObject
 */

void destroyXMLTagObject(XMLTagObject *tagObject);

/**
 * the function is given a pointer to a match object, and updates the match object
 * attributes according to the content of the given xml tag object
 * @param match
 * @param tag
 */

void parseTagObjectToMatchAttribute(CHESS_MATCH *match, XMLTagObject *tag);

/**
 * the functions converting a string representing a row from an xml file,
 * which represents a row from the game board matrix - into am update for the match object
 * this function will be called for each row of the game board
 * @param line
 * @param match
 * @param rowIndex
 */

void parseRowTagLineToMatchAttribute(char *line, CHESS_MATCH *match, int rowIndex);

/**
 * this function combining the function for reading a game board row line from an xml file
 * and parsing that line to perform a the full functionality of parsing game board line from xml to match object
 * @param fp
 * @param buffer
 * @param match
 */

void parseBoardTagFromFileToMatchAttribute(FILE *fp, char* buffer, CHESS_MATCH *match);

#endif //PROJECT_XMLLOADPARSER_H
