//
// Created by okleinfeld on 8/12/2017.
//

#include "XMLSaveParser.h"

int writeMatchObjectToXmlFile(CHESS_MATCH *match, char *addressToFile){
    char *fileContent = transformMatchToXMLString(match);
    if (fileContent == NULL){
        free(fileContent);
        return -1;
    }
    if (writeXMLStringToFile(fileContent, addressToFile) == -1){
        free(fileContent);
        return -1;
    }
    free(fileContent);
    return 0;
}

int writeXMLStringToFile(char *xmlString, char* addressToFile){
    FILE *fp = fopen(addressToFile, "w");
    if (fp == NULL){
        return -1;
    }
    int xmlLength = (int) strlen(xmlString);
    int bytesWritten = (int) fwrite(xmlString, sizeof(char), xmlLength, fp);
    fclose(fp);
    if (bytesWritten == xmlLength) {
        return 0;
    } else {
        return -1;
    }
}

char *transformMatchToXMLString(CHESS_MATCH *match){
    if(match == NULL){
        return NULL;
    }
    char *fileStr = (char *) calloc(MAX_FILE_SIZE, sizeof(char));
    if (fileStr == NULL){
        return NULL;
    }
    strcat(fileStr, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    strcat(fileStr, "<game>\n");
    concatSettingTag(fileStr, "current_turn", match);
    concatSettingTag(fileStr, "game_mode", match);
    if (match->gameMode == 1){
        concatSettingTag(fileStr, "difficulty", match);
        concatSettingTag(fileStr, "user_color", match);
    }
    concatBoardTag(fileStr, match->game);
    strcat(fileStr, "</game>");
    return fileStr;
}


void concatSettingTag(char *fileStr, char *tagName, CHESS_MATCH *match){
    strcat(fileStr, "\t<");
    strcat(fileStr, tagName);
    strcat(fileStr, ">");
    char settingTagValue = getSettingParameterValue(tagName, match);
    appendCharToStringEnd(fileStr, settingTagValue);
    strcat(fileStr, "</");
    strcat(fileStr, tagName);
    strcat(fileStr, ">\n");
}

void concatBoardTag(char *fileStr, CHESS_GAME *game){
    strcat(fileStr, "\t<board>\n");
    char currentRowNum= '8';
    char currentRowChars[9];
    for (int i = nRows; i > 0; --i){
        strcat(fileStr, "\t\t<row_");
        appendCharToStringEnd(fileStr, currentRowNum);
        strcat(fileStr, ">");
        for (int j = 0; j < nCols; ++j){
            currentRowChars[j] = matGet(game->gameBoard, i-1, j);
        }
        currentRowChars[8] = '\0';
        strcat(fileStr, currentRowChars);
        strcat(fileStr, "</row_");
        appendCharToStringEnd(fileStr, currentRowNum);
        strcat(fileStr, ">\n");
        currentRowNum -= 1;
    }
    strcat(fileStr, "\t</board>\n");
}

char getSettingParameterValue(char *paramDescription, CHESS_MATCH *match){
    char valueChar;
    if (strcmp(paramDescription, "current_turn") == 0){
        valueChar = (char) (match->game->currentPlayer + 48);
    } else if (strcmp(paramDescription, "game_mode") == 0){
        valueChar = transformDigitIntToChar(match->gameMode);
    } else if (strcmp(paramDescription, "difficulty") == 0){
        valueChar = transformDigitIntToChar(match->level);
    } else if (strcmp(paramDescription, "user_color") == 0){
        valueChar = transformDigitIntToChar(match->userColor);
    } else{
        valueChar = -1;
    }
    return valueChar;
}

void appendCharToStringEnd(char *destStr, char c){
    char *strPtr = destStr;
    while(*strPtr != '\0'){
        strPtr++;
    }
    *strPtr = c;
    strPtr++;
    *strPtr = '\0';
}

char transformDigitIntToChar(int digit){
    char c;
    c = (char) digit;
    c += 48;
    return c;
}
