//
// Created by okleinfeld on 7/28/2017.
//

#ifndef PROJECT_MATCHMANAGEMENT_H
#define PROJECT_MATCHMANAGEMENT_H

#include "GameRepresenation.h"

typedef struct chess_match {
    int gameMode;
    int level;
    int userColor;
    CHESS_GAME *game;
} CHESS_MATCH;

CHESS_MATCH* createNewChessMatch();

void destroyChessMatch(CHESS_MATCH *match);

void changeMatchGameMode(CHESS_MATCH *match, int newGameMode);

void changeMatchDifficulty(CHESS_MATCH *match, int newDifficulty);

void changeMatchUserColor(CHESS_MATCH *match, int newUserColor);

void resetMatchSettings(CHESS_MATCH *match);

void printMatchSettings(CHESS_MATCH *match);


#endif //PROJECT_MATCHMANAGEMENT_H
