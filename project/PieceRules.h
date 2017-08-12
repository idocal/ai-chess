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
 *
 * @param game
 * @return bool
 */
bool isMoveValid(CHESS_GAME *game, GAME_MOVE *move);

/**
 * Assuming <x,y> is a valid location on the board,
 * returns the piece that is set on the board in the specified location
 *
 *
 * @param game
 * @param move
 * @return PIECE
 */
PIECE pieceByLocation(CHESS_GAME *game, GAME_MOVE *move);





#endif //PROJECT_PIECERULES_H
