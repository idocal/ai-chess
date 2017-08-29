//
// Created by Ido on 8/25/17.
//

#ifndef PROJECT_MINMAXTREE_H
#define PROJECT_MINMAXTREE_H

#include "PieceRules.h"
#include "MinMaxNode.h"

void loopAllPossibleMoves(MIN_MAX_NODE *node, int *maxDepth, bool isRoot, GAME_MOVE **AINextMove);
void evaluateNode(MIN_MAX_NODE *node, int *maxDepth);
GAME_MOVE *AINextMove(CHESS_GAME *game, int *maxDepth);

#endif //PROJECT_MINMAXTREE_H
