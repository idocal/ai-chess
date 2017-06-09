#ifndef SPMINIMAX_H_
#define SPMINIMAX_H_

#include "SPMiniMaxNode.h"

/**
 * Given a game state, this function evaluates the best move according to
 * the current player. The function initiates a MiniMax algorithm up to a
 * specified length given by maxDepth. The current game state doesn't change
 * by this function including the history of previous moves.
 *
 * @param currentGame - The current game state
 * @param maxDepth - The maximum depth of the miniMax algorithm
 * @return
 * -1 if either currentGame is NULL or maxDepth <= 0.
 * On success the function returns a number between [0,SP_FIAR_GAME_N_COLUMNS -1]
 * which is the best move for the current player.
 */

int spMinimaxSuggestMove(SPFiarGame* currentGame,
		unsigned int maxDepth);


/**
 * Generates the root node for the MiniMax tree using createRoot in SPMiniMaxNode.c
 *
 * @param game - A pointer to the game struct.
 * @return
 * NULL if failed to create root node
 * A pointer to the root if the node is created.
 */
node* generateTreeRoot(SPFiarGame* game);

/**
 * Given a root node, generate all other root children accordin to MiniMax algorithm.
 * Generation of each child is performed using generateChildrenNodes.
 * The depth of the tree, maxDepth, is passed as an argument and is chosen in game difficulty.
 *
 * @param game - A pointer to the game struct.
 * @param maxDepth - An integer that detects the depth of the tree generated.
 * @return
 * NULL if and only if one or more of the children could not be generated
 * A pointer to the root of a tree of depth maxDepth
 */
node* generateTree(SPFiarGame* game, int maxDepth);

/**
 * Compute the score of each node in a tree using computeScoreHistogram in SPFIARGame.c
 * The score calculated is updated in node->score
 *
 * @param nodePointer
 * @param optimum
 */
void computeScore(node *nodePointer, OPTIMUM optimum);

/**
 * Frees all memory resources associated with the sub-tree whose root is treeNode. If the
 * source array is NULL, then the function does nothing.
 *
 * @param treeNode - A pointer to the root node of the tree
 */
void destroyTreeNode(node *treeNode);

#endif
