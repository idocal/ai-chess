//
// Created by Ido on 8/25/17.
//

#ifndef PROJECT_MINMAXTREE_H
#define PROJECT_MINMAXTREE_H

#include "PieceRules.h"
#include "MinMaxNode.h"

MIN_MAX_NODE *createChildrenEmptyNodesList(MIN_MAX_NODE *parent, int *maxDepth);

/**
 *
 * @param node
 * @param game
 * @param maxDepth
 * @return -1 if error occurred,
 * 0 if alpha-beta pruning was activated,
 * 1 if value should be moved forward through the tree.
 */
int evaluateNode(MIN_MAX_NODE *node, CHESS_GAME *game, int *maxDepth);

GAME_MOVE *AINextMove(CHESS_GAME *game, int *maxDepth);

#endif //PROJECT_MINMAXTREE_H
