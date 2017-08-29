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

void loopAllPossibleMoves(MIN_MAX_NODE *node, int *maxDepth, bool isRoot, GAME_MOVE **AINextMove, bool isExpert);
void evaluateNode(MIN_MAX_NODE *node, int *maxDepth, bool isExpert);
GAME_MOVE *AINextMove(CHESS_GAME *game, int *maxDepth, bool isExpert);

#endif //PROJECT_MINMAXTREE_H
