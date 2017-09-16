//
// Created by Ido on 8/25/17.
//

#ifndef PROJECT_MINMAXNODE_H
#define PROJECT_MINMAXNODE_H

#include "GameMoves.h"
#include "limits.h"
#include "stdbool.h"

#define opposite(type) ((type == MIN) ? MAX : MIN)
#define opponent(player) ((char) (1 - player))

typedef enum nodeType {
    MIN,
    MAX
} NODE_TYPE;

typedef struct minMaxNode {
    NODE_TYPE type;
    CHESS_GAME *game;
    GAME_MOVE *move;
    int value;
    int alpha;
    int beta;
    bool isLeaf;
    int depth;
} MIN_MAX_NODE;

MIN_MAX_NODE *createMinMaxNode(NODE_TYPE type, CHESS_GAME *game, GAME_MOVE *move, int alpha, int beta, int depth, int *maxDepth);

void destroyNode(MIN_MAX_NODE *node);

MIN_MAX_NODE *createTreeRoot(NODE_TYPE type, CHESS_GAME *game);

#endif //PROJECT_MINMAXNODE_H
