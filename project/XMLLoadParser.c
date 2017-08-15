//
// Created by okleinfeld on 8/15/2017.
//

#include "XMLLoadParser.h"

void readLineFromFileIntoBuffer(FILE* fp, char* buffer){
    if (fp == NULL){
        return;
    }
    char c;
    while ((c = fgetc(fp)) != '\n'){
        if (c == '\r'){
            continue;
        } else{
            *buffer = c;
            buffer++;
        }
    }
    *buffer = '\0';
}

XmlTag parseTagNameStringToEnum(char* tagName){
    XmlTag tag = INVALID_TAG_NAME;
    if (strcmp(tagName, "current_turn") == 0){
        tag = CURRENT_TURN_TAG;
    } else if (strcmp(tagName, "game_mode") == 0){
        tag = GAME_MODE_TAG;
    } else if (strcmp(tagName, "difficulty") == 0){
        tag = DIFFICULTY_TAG;
    } else if (strcmp(tagName, "user_color") == 0){
        tag = USER_COLOR_TAG;
    }
    return tag;
}

XMLTagObject* parseXmlLineToTagObject(char* line){
    char tagName[MAX_LINE_LENGTH];
    char tagValue;
    int tagNameCounter = 0;
    while (*line != '<'){
        line++;
    }
    line++;
    while (*line != '>'){
        tagName[tagNameCounter] = *line;
        line++;
        tagNameCounter++;
    }
    line++;
    tagName[tagNameCounter] = '\0';
    tagValue = *line;
    XMLTagObject *tag = malloc(sizeof(XMLTagObject));
    tag->tagName = parseTagNameStringToEnum(tagName);
    tag->tagValue = tagValue - 48;
    return tag;
}

