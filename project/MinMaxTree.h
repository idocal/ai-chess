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
#include <time.h>

typedef enum {
    GAME_OVER_CHECK_MATE,
    GAME_OVER_TIE,
    NODE_IS_LEAF,
    NOT_TERMINATING
} TERMINATING_CONDITION;


GAME_MOVE *AINextMove(CHESS_GAME *game, int *maxDepth, bool isExpert);

TERMINATING_CONDITION isTerminalNode(MIN_MAX_NODE *node);

void updateScoreForTerminatingNode(MIN_MAX_NODE *node, TERMINATING_CONDITION stopReason, bool isExpert);

#endif //PROJECT_MINMAXTREE_H
