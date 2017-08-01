//
// Created by okleinfeld on 7/28/2017.
//

#ifndef PROJECT_MATCHMANAGEMENT_H
#define PROJECT_MATCHMANAGEMENT_H

#include "GameRepresenation.h"

/**
 * MatchManagement Summary:
 *
 * The structures and functions defined in this header consolidates together with
 * the GameRepresentation interface to represent an end to end abstraction of  a Chess Match.
 *
 */



/**
 * This Structure is used to represent a full abstraction of chess match
 * it contains global fields from the game setting phase such as the game mode level and user color
 * and also contains as a filed a pointer to a Chess_Game structure to represent the current status
 * of the game board.
 *
 */
typedef struct chess_match {
    int gameMode;
    int level;
    int userColor;
    CHESS_GAME *game;
} CHESS_MATCH;


/**
 * Creates a new chess match object and return a pointer to it.
 * Preforms all the memory allocation commands needed.
 *
 * Each game-setting field value corresponds to the correct default value specified in the project's instructions
 * Also notice that the game board is not(!) initialized
 *
 * @return
 * NULL if  a memory allocation failure occurs.
 * Otherwise, a pointer to a new chess match instance is returned.
 */
CHESS_MATCH* createNewChessMatch();


/**
 * Frees all memory attached with the chessMatch object
 * Including freeing all the memory attached with the encapsulated ChessGame object
 * (assuming this function will get called when a match is over)
 *
 * @param match - pointer to a given ChessMatch object
 */
void destroyChessMatch(CHESS_MATCH *match);

/**
 * A "Setter" for the structure filed - Game Mode
 *
 * @param
 * match - pointer to a given ChessMatch object
 * newGameMode - the value of the desired newGameMode field.
 */
void changeMatchGameMode(CHESS_MATCH *match, int newGameMode);

/**
 * A "Setter" for the structure filed - Match Difficulty
 *
 * @param
 * match - pointer to a given ChessMatch object
 * newDifficulty - the value of the desired Difficulty field.
 */
void changeMatchDifficulty(CHESS_MATCH *match, int newDifficulty);


/**
 * A "Setter" for the structure filed - User Color
 *
 * @param
 * match - pointer to a given ChessMatch object
 * newUserColor- the value of the desired User Color field.
 */
void changeMatchUserColor(CHESS_MATCH *match, int newUserColor);

/**
 * Reset all the structure's field to their default values as specified in the project's instructions.
 * (Doesn't change the ChessGame object at all)
 *
 *
 * @param
 * match - pointer to a given ChessMatch object
 */
void resetMatchSettings(CHESS_MATCH *match);


/**
 * Print the current match setting in the specified format
 *
 * @param
 * match - pointer to a given ChessMatch object
 */
void printMatchSettings(CHESS_MATCH *match);


#endif //PROJECT_MATCHMANAGEMENT_H
