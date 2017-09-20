//
// Created by Ido on 8/25/17.
//

#ifndef PROJECT_SCORING_H
#define PROJECT_SCORING_H

#include "PieceRules.h"

#define opponent(player) ((char) (1 - player))

/**
 * compute the naive scoring function as described in the instructions
 * @param game pointer
 * @return naive score
 */

int score(CHESS_GAME *game);


/**
 * compute the leaf scoring function on expert mode
 * the function is a weighted combination of the naive scoring function
 * together if other known chess heuristics
 * @param game pointer
 * @return expert score
 */


int expertScore(CHESS_GAME *game);

#endif //PROJECT_SCORING_H
