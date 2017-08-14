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

bool isOutOfBounds(int x, int y);

bool isSlotOccupied(CHESS_GAME *game, int x, int y, char playerMoved);

bool isGameCheck(CHESS_GAME *game, char playerChecked);

bool isMovePossible(CHESS_GAME *game, GAME_MOVE *move, bool includeCheck);

/**
 * Assuming <x,y> is a valid location on the board,
 * Find out which type of piece is set on <x,y>
 *
 * @param game
 * @param move
 * @return the piece that is set on the board in the specified location
 */
PIECE pieceByLocation(CHESS_GAME *game, GAME_MOVE *move);

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
 * Calculate the bishop's possible moves according to location <x,y>
 * and a specified game state
 *
 * @param game
 * @param x (row)
 * @param y (column)
 * @return matrix with 1's where move is possible and 0 where move is impossible
 */
MATRIX *bishopPossibleMoves(CHESS_GAME *game, int x, int y);

/**
 * Calculate the rook's possible moves according to location <x,y>
 * and a specified game state
 *
 * @param game
 * @param x (row)
 * @param y (column)
 * @return matrix with 1's where move is possible and 0 where move is impossible
 */
MATRIX *rookPossibleMoves(CHESS_GAME *game, int x, int y);

/**
 * Calculate the knight's possible moves according to location <x,y>
 * and a specified game state
 *
 * @param game
 * @param x (row)
 * @param y (column)
 * @return matrix with 1's where move is possible and 0 where move is impossible
 */
MATRIX *knightPossibleMoves(CHESS_GAME *game, int x, int y);


/**
 * Calculate the queen's possible moves according to location <x,y>
 * and a specified game state
 *
 * @param game
 * @param x (row)
 * @param y (column)
 * @return matrix with 1's where move is possible and 0 where move is impossible
 */
MATRIX *queenPossibleMoves(CHESS_GAME *game, int x, int y);

/**
 * Calculate the king's possible moves according to location <x,y>
 * and a specified game state
 *
 * @param game
 * @param x (row)
 * @param y (column)
 * @return matrix with 1's where move is possible and 0 where move is impossible
 */
MATRIX *kingPossibleMoves(CHESS_GAME *game, int x, int y);


#endif //PROJECT_PIECERULES_H
