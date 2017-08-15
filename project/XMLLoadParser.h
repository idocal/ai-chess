//
// Created by okleinfeld on 8/15/2017.
//

#ifndef PROJECT_XMLLOADPARSER_H
#define PROJECT_XMLLOADPARSER_H

#include "MatchManagement.h"
#include "XMLSaveParser.h"
#include <string.h>

#define MAX_LINE_LENGTH 1024

typedef enum xml_tag {
    CURRENT_TURN_TAG,
    GAME_MODE_TAG,
    DIFFICULTY_TAG,
    USER_COLOR_TAG,
    INVALID_TAG_NAME
} XmlTag;


typedef struct xml_tag_object {
    XmlTag tagName;
    int tagValue;
} XMLTagObject;


void readLineFromFileIntoBuffer(FILE *fp, char* buffer);

XmlTag parseTagNameStringToEnum(char* tagName);

XMLTagObject* parseXmlLineToTagObject(char* line);

#endif //PROJECT_XMLLOADPARSER_H
