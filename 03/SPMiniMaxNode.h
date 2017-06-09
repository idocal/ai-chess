#ifndef SPMINIMAXNODE_H_
#define SPMINIMAXNODE_H_

#include "SPFIARGame.h"

/**
 * Each tree node contains:
 * game
 * 7 children
 * score
 * depth
 * leaf flag
 */
typedef struct node
{
    SPFiarGame *game;
    struct node *children[7];
    int score;
    int depth;
    bool isLeaf;
} node;

/**
 * Special enum for optimums.
 */
typedef enum optimum_t {
    MIN_NODE,
    MAX_NODE
} OPTIMUM;

/**
 * Creates the actual node which means memory allocation,
 * Copying a game struct and attach it to the node (we dont want to edit the actual game),
 * Set the move to the copy of the game.
 * Initiate score to 0,
 * Update depth, given as an arg by recursion,
 * If node is in depth maxDepth, then it's a leaf.
 *
 *
 * @param game - A pointer to the game struct.
 * @param depth - The depth of the node created.
 * @param moveColumn - The move that should be performed.
 * @param maxDepth - The difficulty
 * @return
 * NULL if an error occured in memory allocation.
 * A pointer to the node if succeeded to create.
 */
node *createNode(SPFiarGame *game, int depth, int moveColumn, int maxDepth);

/**
 * Creates a root node which means memory allocation,
 * Set initial score, depth, and isLeaf.
 *
 * @param game - A pointer to the game struct.
 * @return
 * NULL if an error occured in memory allocation.
 * A pointer to the node if succeeded to create.
 */
node *createRoot(SPFiarGame *game);

/**
 * Frees all memory resources associated with the node. If the
 * source array is NULL, then the function does nothing.
 *
 * @param nodePointer - A pointer to the root node of the tree
 */
void nodeDestroy(node *nodePointer);

#endif
