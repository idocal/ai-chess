//
// Created by okleinfeld on 8/15/2017.
//

#include "XMLLoadParser.h"

CHESS_MATCH* parseXMLGameFile(char *fileAddress){
    FILE *fp = fopen(fileAddress, "r");
    if (fp == NULL){
        return NULL;
    }
    char * buffer = malloc(sizeof(char) * MAX_LINE_LENGTH);
    if (buffer == NULL){
        fclose(fp);
        return NULL;
    }
    CHESS_MATCH * match = createNewChessMatch();
    if (match == NULL){
        fclose(fp);
        free(buffer);
        return NULL;
    }
    readLineFromFileIntoBuffer(fp, buffer); // read header xml line
    readLineFromFileIntoBuffer(fp, buffer); // read "<game>" tag line
    for (int i = 0; i < 2; ++i){ // parse 2 lines of game setting tags (current turn and game mode will always appear)
        readLineFromFileIntoBuffer(fp, buffer);
        XMLTagObject *tag = parseXmlLineToTagObject(buffer);
        parseTagObjectToMatchAttribute(match, tag); //
        destroyXMLTagObject(tag); // free the Tag object memory!
    }
    if (match->gameMode == 1){ // if the mode is 1 player need to parse also difficulty and user color
        for (int i = 0; i < 2; ++i){
            readLineFromFileIntoBuffer(fp, buffer);
            XMLTagObject *tag = parseXmlLineToTagObject(buffer);
            parseTagObjectToMatchAttribute(match, tag); //
            destroyXMLTagObject(tag); // free the Tag object memory!
        }
    }
    parseBoardTagFromFileToMatchAttribute(fp, buffer, match); // parse the board content part
    readLineFromFileIntoBuffer(fp, buffer); // read the "</game>" tag line
    fclose(fp); // close file
    free(buffer); // free read line buffer
    return match;
}

void readLineFromFileIntoBuffer(FILE* fp, char* buffer){
    if (fp == NULL){
        return;
    }
    char c;
    while ((c = fgetc(fp)) != '\n'){
        if (c == '\r'){
            continue;
        } else if (c == EOF){
            break;
        } else {
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

void parseTagObjectToMatchAttribute(CHESS_MATCH *match, XMLTagObject *tag){
    if (match == NULL || tag == NULL)
        return;
    if (tag->tagName == INVALID_TAG_NAME)
        return;
    if (tag->tagName == GAME_MODE_TAG){
        match->gameMode = tag->tagValue;
    } else if (tag->tagName == CURRENT_TURN_TAG){
        match->game->currentPlayer = tag->tagValue;
    } else if (tag->tagName == DIFFICULTY_TAG){
        match->level = tag->tagValue;
    } else if (tag ->tagName == USER_COLOR_TAG) {
        match->userColor = tag->tagValue;
    }
}

void parseBoardTagFromFileToMatchAttribute(FILE *fp, char* buffer, CHESS_MATCH *match){
    readLineFromFileIntoBuffer(fp, buffer); // read the "<board>" line
    for (int i = nRows -1; i >= 0; --i){
        readLineFromFileIntoBuffer(fp, buffer); // read "<row_x>" line
        parseRowTagLineToMatchAttribute(buffer, match, i); // update the game board with the line values
    }
    readLineFromFileIntoBuffer(fp, buffer); // read the "</board>" line
}

void parseRowTagLineToMatchAttribute(char *line, CHESS_MATCH *match, int rowIndex){
    while (*line != '>'){
        line++;
    }
    line++;
    for (int j = 0; j < nCols; ++j){
        matSet(match->game->gameBoard, rowIndex, j, *line);
        line++;
    }
}

void destroyXMLTagObject(XMLTagObject *tagObject){
    if (tagObject == NULL) {
        return;
    }
    free(tagObject);
}
