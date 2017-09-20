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

/**
 * an enum representing two types of a MinMax node
 */
typedef enum nodeType {
    MIN,
    MAX
} NODE_TYPE;

/**
 * a structure representing a MinMax node object
 * each node consist of his type, game state (game pointer + move to perform)
 * the node value, alpha and beta values (calculated directly if leaf, recursively otherwise)
 * and the node's depth indication
 */

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


/**
 * a constructor for a new MinMax node. with default values for the node's attributes -
 * depending on the node's type.
 * @param type
 * @param game
 * @param move
 * @param alpha
 * @param beta
 * @param depth
 * @param maxDepth
 * @return a pointer to a new MinMax node object
 */

MIN_MAX_NODE *createMinMaxNode(NODE_TYPE type, CHESS_GAME *game, GAME_MOVE *move, int alpha, int beta, int depth, int *maxDepth);


/**
 * a destructor for a MinMax node object. frees all of the node's associated memory
 * (the move object is allocated outside the MinMax node constructor and will be freed during the algorithm)
 * this is a joint destructor for regular and root nodes.
 * @param node
 */

void destroyNode(MIN_MAX_NODE *node);

/**
 * a special case constructor for the root of the MinMax tree.
 *
 * @param type
 * @param game
 * @return a pointer to the root of the MinMax algorithm tree
 */

MIN_MAX_NODE *createTreeRoot(NODE_TYPE type, CHESS_GAME *game);

#endif //PROJECT_MINMAXNODE_H
