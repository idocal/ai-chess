//
// Created by Ido on 8/25/17.
//

#ifndef PROJECT_MINMAXNODE_H
#define PROJECT_MINMAXNODE_H

#include "GameMoves.h"
#include "limits.h"
#include "stdbool.h"

typedef enum nodeType {
    MIN,
    MAX
} NODE_TYPE;

typedef struct minMaxNode {
    NODE_TYPE type;
    CHESS_GAME *game;
    GAME_MOVE *move;
    struct minMaxNode *children;
    struct minMaxNode *next;
    int value;
    int alpha;
    int beta;
    bool isLeaf;
    char depth;
} MIN_MAX_NODE;

MIN_MAX_NODE *createEmptyNode(NODE_TYPE type, GAME_MOVE *move, int alpha, int beta, char depth, char *maxDepth);

void destroyNode(MIN_MAX_NODE *node);

MIN_MAX_NODE *createTreeRoot(NODE_TYPE type, CHESS_GAME *game, char *maxDepth);

#endif //PROJECT_MINMAXNODE_H
