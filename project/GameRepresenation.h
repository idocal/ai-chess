//
// Created by okleinfeld on 7/27/2017.
//

#ifndef PROJECT_GAMEREPRESENATION_H
#define PROJECT_GAMEREPRESENATION_H

#include <stdlib.h>
#include <stdio.h>
#define nRows 8
#define nCols 8

/**
 * GameRepresentation Summary:
 *
 * This header contains definitions for structures and enums for abstracting 
 * a snapshot of a chess game status and a game move
 * the header doesn't contain the structure that includes the game setting,
 * this can be found in the "MatchManagement" header
 *
 * createEmptyGame           - Creates a new empty/default status game (just '_' all over to board)
 * initGameBoard             - Initiate the game board to represent a valid chess game initial state
 * copyChessGame             - Copy an existing chess game structure (create a deep copy)
 * printChessGameBoard      - Print according to representation detailed in the instructions doc
 * destroyChessGame         - Free all memory attached with a given chess game object
 * createGameMove           - Creates a new game move object that represents a single game mover
 * destroyGameMove          - Free all memory attached with a given game move object
 */

/**
 * enum, encapsulating a special game status
 */
typedef enum game_status {
    REGULAR,
    CHECK,
    MATE,
    TIE,
} GAME_STATUS;


/**
 * Structure used to represent a snapshot of a current game status
 * (without including general information mutual to the entire game such as game mode etc.)
 *
 * Notice that the representation of the game board matrix is done using two dimensional arrays -
 * the first one is a pointer array including 8 pointers each point to a beginning of a matrix row
 * the second is the actual matrix represented using a flat one dimension 64 entries array
 */
typedef struct chess_game {
    char **gameBoard;
    GAME_STATUS status;
    char currentPlayer;
} CHESS_GAME;


/**
 * Structure used to represent a game move object
 * Will be later saved in a special "Stack" data structure for history and undo command management
 */
typedef struct game_move {
    int sourceRowIndex;
    int sourceColIndex;
    int destRowIndex;
    int destColIndex;
    char sourceOriginalSymbol;
    char destOriginalSymbol;
} GAME_MOVE;


/**
 * Creates a new empty/default chess game and return a pointer to it.
 * Preforms all the memory allocation commands needed.
 *
 * @return
 * NULL if  a memory allocation failure occurs.
 * Otherwise, a pointer to a new game instant is returned.
 */
CHESS_GAME* createEmptyGame();


/**
 * Copy a given chess game and return a pointer to the new copy created.
 * Notice that the copy preforms "deep copy" not pointing to the same memory addresses but
 * allocating a different memory for the copied instance.
 *
 * @param pointer to a valid chess game object.
 *
 * @return
 * NULL if  a memory allocation failure occurs.
 * Otherwise, a pointer to a the copied game instant is returned.
 */
CHESS_GAME* copyChessGame(CHESS_GAME *);


/**
 * Frees all the memory related with a given chess game object
 *
 * @param pointer to a valid chess game object.
 */
void destroyChessGame(CHESS_GAME *);


/**
 * Changes the content of the given game's board
 * Transforming an empty board (or any other board status) to the state of a valid
 * chess game board
 *
 * @param pointer to a valid chess game object.
 *
 */
void initGameBoard(CHESS_GAME *);

/**
 * Prints a representation of a given chess game board according to
 * the representation detailed in the instructions.
 *
 * @param pointer to a valid chess game object.
 */
void printChessGameBoard(CHESS_GAME *);


/**
 * Creates a new game move object to be later stored in a Stack data structure
 *
 * @param
 * source row number (0 based)
 * source column number (0 based)
 * destination row number (0 based)
 * destination column number (0 based)
 *
 * @return
 * NULL if  a memory allocation failure occurs.
 * Otherwise, a pointer to a the new game move instance.
 */
GAME_MOVE* createGameMove(CHESS_GAME *, int, int, int, int);



/**
 * Frees all the memory allocated fot the given game move instance
 *
 * @param pointer to a valid game move object.
 */
void destroyGameMove(GAME_MOVE *);

#endif //PROJECT_GAMEREPRESENATION_H
