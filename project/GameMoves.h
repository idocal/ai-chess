//
// Created by Ido on 8/20/17.
//

#ifndef PROJECT_GAMEMOVES_H
#define PROJECT_GAMEMOVES_H

#include "GameRepresenation.h"


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
GAME_MOVE* createGameMove(CHESS_GAME *, int sourceRow, int sourceCol, int destRow, int destCol);



/**
 * Frees all the memory allocated fot the given game move instance
 *
 * @param pointer to a valid game move object.
 */
void destroyGameMove(GAME_MOVE *);

/**
 * Performs the move on the actual game board.
 * This function changes the game->gameBoard matrix,
 * so in some cases it is necessary to provide with a copy
 * this can be achieved via copy copyChessGame function.
 *
 * @param game
 * @param move
 */
void performMove(CHESS_GAME *game, GAME_MOVE *move);

/**
 * Performs the INVERSE move on the actual game board.
 * This function changes the game->gameBoard matrix,
 * so in some cases it is necessary to provide with a copy
 * this can be achieved via copy copyChessGame function.
 * Reverting is useful for Undo actions.
 *
 * @param game
 * @param move
 */
void revertMove(CHESS_GAME *game, GAME_MOVE *move);

#endif //PROJECT_GAMEMOVES_H
