//
// Created by okleinfeld on 7/28/2017.
//

#include "MatchManagement.h"

CHESS_MATCH* createNewChessMatch(){
    CHESS_MATCH *chess_match = (CHESS_MATCH *) malloc(sizeof(CHESS_MATCH));
    if (chess_match == NULL){
        return NULL;
    }
    chess_match->game = createEmptyGame(); // Create also ChessGame object
    if (chess_match->game == NULL){
        free(chess_match);
        return NULL;
    }
    chess_match->gameMode = 1;
    chess_match->level = 2;
    chess_match->userColor = 1;
    return chess_match;
}

void destroyChessMatch(CHESS_MATCH *match){
    if (match == NULL){
        return;
    }
    destroyChessGame(match->game); // have to first free memory attached with ChessGame object
    free(match);
}


void resetMatchSettings(CHESS_MATCH *match){
    if (match == NULL){
        return;
    }
    match->gameMode = 1;
    match->level = 2;
    match->userColor = 1;
}

void printMatchSettings(CHESS_MATCH *match){
    if (match == NULL){
        return;
    }
    printf("SETTINGS:\n");
    if (match->gameMode == 1){
        printf("GAME_MODE: 1\n");
        printf("DIFFICULTY_LVL: %d\n", match->level);
        if (match->userColor == 1){
            printf("USER_CLR: WHITE\n");
        } else{
            printf("USER_CLR: BLACK\n");
        }
    } else{ // if two users play against each other, no meaning for difficulty and user color
        printf("GAME_MODE: 2\n");
    }
}

