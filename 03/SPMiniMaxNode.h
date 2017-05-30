#ifndef SPMINIMAXNODE_H_
#define SPMINIMAXNODE_H_

#include "SPFIARGame.h"
#define USER_DIFFICULTY 2

typedef struct node
{
    SPFiarGame *game;
    struct node *children[7];
    int score;
    int depth;
    bool isLeaf;
} node;

node *createNode(SPFiarGame *game, int depth, int moveColumn);
node *createRoot(SPFiarGame *game);

void nodeDestroy(node *nodePointer);

#endif
