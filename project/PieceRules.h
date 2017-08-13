//
// Created by Ido on 8/12/17.
//
#include <stdbool.h>
#include "GameRepresenation.h"

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
 * Assuming <x,y> is a valid location on the board,
 * Find out which type of piece is set on <x,y>
 *
 * @param game
 * @param move
 * @return the piece that is set on the board in the specified location
 */
PIECE pieceByLocation(CHESS_GAME *game, GAME_MOVE *move);

/**
 * Calculate the pawn's possible moves according to location <x,y>
 * and a specified game state
 *
 * @param game
 * @param x (row)
 * @param y (column)
 * @return matrix with 1's where move is possible and 0 where move is impossible
 */
char **pawnPossibleMoves(CHESS_GAME *game, int x, int y);

/**
 * Calculate the bishop's possible moves according to location <x,y>
 * and a specified game state
 *
 * @param game
 * @param x (row)
 * @param y (column)
 * @return matrix with 1's where move is possible and 0 where move is impossible
 */
char **bishopPossibleMoves(CHESS_GAME *game, int x, int y);

/**
 * Calculate the rook's possible moves according to location <x,y>
 * and a specified game state
 *
 * @param game
 * @param x (row)
 * @param y (column)
 * @return matrix with 1's where move is possible and 0 where move is impossible
 */
char **rookPossibleMoves(CHESS_GAME *game, int x, int y);

/**
 * Calculate the knight's possible moves according to location <x,y>
 * and a specified game state
 *
 * @param game
 * @param x (row)
 * @param y (column)
 * @return matrix with 1's where move is possible and 0 where move is impossible
 */
char **knightPossibleMoves(CHESS_GAME *game, int x, int y);


/**
 * Calculate the queen's possible moves according to location <x,y>
 * and a specified game state
 *
 * @param game
 * @param x (row)
 * @param y (column)
 * @return matrix with 1's where move is possible and 0 where move is impossible
 */
char **queenPossibleMoves(CHESS_GAME *game, int x, int y);

/**
 * Calculate the king's possible moves according to location <x,y>
 * and a specified game state
 *
 * @param game
 * @param x (row)
 * @param y (column)
 * @return matrix with 1's where move is possible and 0 where move is impossible
 */
char **kingPossibleMoves(CHESS_GAME *game, int x, int y);

#endif //PROJECT_PIECERULES_H
