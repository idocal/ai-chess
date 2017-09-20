//
// Created by Ido on 8/25/17.
//

#ifndef PROJECT_MINMAXTREE_H
#define PROJECT_MINMAXTREE_H

#include "PieceRules.h"
#include "MinMaxNode.h"
#include "Scoring.h"
#include "GameStates.h"
#include <stdlib.h>

/**
 * the function loops over all possible moves of a current game node,
 * creating a child node, one node at a time limiting the memory complexity to O(d) at any given time
 * wheres d is the MinMax tree depth.
 * for each crated node calling the "evaluateNode" function until stopping criterion is reached.
 *
 *
 * @param node
 * @param maxDepth
 * @param isRoot
 * @param AINextMove
 * @param isExpert
 *
 *
 */

void loopAllPossibleMoves(MIN_MAX_NODE *node, int *maxDepth, bool isRoot, GAME_MOVE **AINextMove, bool isExpert);

/**
 * the function evaluates the node's scoring values either directly (leaf, pruning or checkmate/tie condition)
 * or recursively by calling the function loopAllPossibleMoves the compute the values of the node's children.
 * after evaluating the node's scoring value the "value" attribute and alpha/beta value are updated
 *
 * @param node
 * @param maxDepth
 * @param isExpert
 */

void evaluateNode(MIN_MAX_NODE *node, int *maxDepth, bool isExpert);

/**
 * interface function for the MinMAx AI algorithm
 * creating the tree root and computing the MinMax algorithm
 * returning a chosen move to perform which heuristically optimizes the root's scoring function
 *
 * @param game
 * @param maxDepth
 * @param isExpert
 * @return a pointer to a game move object - the move the computer should perform
 */

GAME_MOVE *AINextMove(CHESS_GAME *game, int *maxDepth, bool isExpert);

#endif //PROJECT_MINMAXTREE_H
