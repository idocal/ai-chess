//
// Created by Ido on 8/12/17.
//
#include <stdbool.h>
#include "GameRepresenation.h"
#include "GameAux.h"

#ifndef PROJECT_PIECERULES_H
#define PROJECT_PIECERULES_H

typedef enum {
    PAWN,
    BISHOP,
    ROOK,
    KNIGHT,
    QUEEN,
    KING,
    BLANK
} PIECE;


/**
 * Check if a move is valid according to the piece type and game state
 *
 * @param game
 * @param move
 * @return true iff move is valid
 */
bool isMoveValid(CHESS_GAME *game, GAME_MOVE *move);

/**
 * Detect who owns a certain piece, relative to the player "asking"
 *
 * @param piece
 * @param player (0 black, 1 white)
 * @return 1 if piece is player's , 0 if piece is opponent's and -1 if blank
 */
char pieceOwner(char piece, char player);

/**
 * Detect if moving to an invalid location (i.e. out of the border)
 *
 * @param x (row)
 * @param y (column)
 * @return true iff the desired location is out of the board.
 */
bool isOutOfBounds(int x, int y);

/**
 * Detect if the slot which the player wants to move in is already occupied
 * by another piece of the player.
 *
 * @param game
 * @param x
 * @param y
 * @param playerMoved - the player (0 black,1 white) that performs the move
 * @return true iff slot is occupied
 */
bool isSlotOccupied(CHESS_GAME *game, int x, int y, char playerMoved);

/**
 * Detect if the game is in Check situation,
 * this means that opponent owns one or more pieces which
 * are able to move to the player's king location on next move.
 *
 * @param game
 * @param playerChecked - the player (0 black,1 white) that is being Checked
 * @return true iff the player is Checked
 */
bool isGameCheck(CHESS_GAME *game, char playerChecked);

/**
 * Decide whether a certain move is possible by:
 * Slot occupation or
 * Out of bounds or
 * Player Checked on next move (if allowed includeCheck)
 *
 * @param game
 * @param move
 * @param player
 * @param includeCheck - this is important because in Check certifying a move is possible even if it leads to a counter-Check
 * @return
 */
bool isMovePossible(CHESS_GAME *game, GAME_MOVE *move, char player, bool includeCheck);

/**
 * Add to the movesMatrix linear possible slots.
 * This function computes possibleMoves of a given direction (up and right)
 * For example: diagonal move up-right is (1,1) and horizontal move left is (-1,0)
 * This function is used by addOrthogonalMoves and addDiagonalMoves.
 * If a slot is not a possible move, the function stops "going" in the specified direction.
 * If a slot is opponent's (that is, conquering) the function stops "going" in the specified direction.
 *
 * @param movesMatrix
 * @param game
 * @param x
 * @param y
 * @param player
 * @param includeCheck - this is important because in Check certifying a move is possible even if it leads to a counter-Check
 * @param right (-1, 0, 1)
 * @param up (-1, 0, 1)
 */

/**
 * Test if a certain location is a valid possibility using isMovePossible.
 * If it is, mark it with marker on the movesMatrix.
 *
 * @param movesMatrix
 * @param game
 * @param x
 * @param y
 * @param player
 * @param includeCheck
 * @param marker (1,2)
 */
void testPossibility(MATRIX *movesMatrix, CHESS_GAME *game, int x, int y, char player, bool includeCheck, int marker);

/**
 * Perform a linear move change on the movesMatrix.
 * The linear direction is provided by (x,y) -
 * For example: up-right is (1,1) and left is (0,-1)
 *
 * @param movesMatrix
 * @param game
 * @param x
 * @param y
 * @param player
 * @param includeCheck
 * @param right
 * @param up
 */
void linearMoves(MATRIX *movesMatrix, CHESS_GAME *game, int x, int y, char player, bool includeCheck, int right, int up);

/**
 * Orthogonal moves are right, left, up and down.
 * This function uses linearMoves to add to the movesMatrix of a certain piece
 * all the orthogonal possible moves
 *
 * @param movesMatrix
 * @param game
 * @param x
 * @param y
 * @param player
 * @param includeCheck - this is important because in Check certifying a move is possible even if it leads to a counter-Check
 */
void addOrthogonalMoves(MATRIX *movesMatrix, CHESS_GAME *game, int x, int y, char player, bool includeCheck);

/**
 * Diagonal moves are right-up, right-down, left-up, left-down.
 * This function uses linearMoves to add to the movesMatrix of a certain piece
 * all the diagonal possible moves
 *
 * @param movesMatrix
 * @param game
 * @param x
 * @param y
 * @param player
 * @param includeCheck - this is important because in Check certifying a move is possible even if it leads to a counter-Check
 */
void addDiagonalMoves(MATRIX *movesMatrix, CHESS_GAME *game, int x, int y, char player, bool includeCheck);

/**
 * Assuming <x,y> is a valid location on the board,
 * Find out which type of piece is set on <x,y>
 *
 * @param game
 * @param move
 * @return the piece that is set on the board in the specified location
 */
PIECE pieceByLocation(CHESS_GAME *game, GAME_MOVE *move);

/**
 * Calls one of the functions below to retrieve movesMatrix,
 * a 0/1 matrix that represents possible moves for a certain piece.
 * 1 is where piece can move, 0 where it cannot.
 *
 * @param game
 * @param piece type (char symbol)
 * @param x - piece's row location
 * @param y - piece's column location
 * @param includeCheck - this is important because in Check certifying a move is possible even if it leads to a counter-Check
 * @return the movesMatrix defined above
 */
MATRIX *piecePossibleMoves(CHESS_GAME *game, char piece, int x, int y, bool includeCheck);

/**
 * Calculate the pawn's possible moves according to location <x,y>
 * and a specified game state
 *
 * @param game
 * @param x (row)
 * @param y (column)
 * @return matrix with 1's where move is possible and 0 where move is impossible
 */
MATRIX *pawnPossibleMoves(CHESS_GAME *game, int x, int y, char player, bool includeCheck);

/**
 * Calculate the rook's possible moves according to location <x,y>
 * and a specified game state
 *
 * @param game
 * @param x (row)
 * @param y (column)
 * @return matrix with 1's where move is possible and 0 where move is impossible
 */
MATRIX *rookPossibleMoves(CHESS_GAME *game, int x, int y, char player, bool includeCheck);

/**
 * Calculate the bishop's possible moves according to location <x,y>
 * and a specified game state
 *
 * @param game
 * @param x (row)
 * @param y (column)
 * @return matrix with 1's where move is possible and 0 where move is impossible
 */
MATRIX *bishopPossibleMoves(CHESS_GAME *game, int x, int y, char player, bool includeCheck);

/**
 * Calculate the queen's possible moves according to location <x,y>
 * and a specified game state
 *
 * @param game
 * @param x (row)
 * @param y (column)
 * @return matrix with 1's where move is possible and 0 where move is impossible
 */
MATRIX *queenPossibleMoves(CHESS_GAME *game, int x, int y, char player, bool includeCheck);

/**
 * Calculate the king's possible moves according to location <x,y>
 * and a specified game state
 *
 * @param game
 * @param x (row)
 * @param y (column)
 * @return matrix with 1's where move is possible and 0 where move is impossible
 */
MATRIX *kingPossibleMoves(CHESS_GAME *game, int x, int y, char player, bool includeCheck);

#endif //PROJECT_PIECERULES_H
