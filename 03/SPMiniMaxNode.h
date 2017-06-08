#ifndef SPMINIMAXNODE_H_
#define SPMINIMAXNODE_H_

#include "SPFIARGame.h"

typedef struct node
{
    SPFiarGame *game;
    struct node *children[7];
    int score;
    int depth;
    bool isLeaf;
} node;

typedef enum optimum_t {
    MIN_NODE,
    MAX_NODE
} OPTIMUM;

node *createNode(SPFiarGame *game, int depth, int moveColumn, int maxDepth);

node *createRoot(SPFiarGame *game);

void nodeDestroy(node *nodePointer);

#endif