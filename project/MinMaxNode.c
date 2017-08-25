//
// Created by Ido on 8/25/17.
//

#include "MinMaxNode.h"

#define SUFFICIENT_MIN -10000
#define SUFFICIENT_MAX 10000

bool isLeaf(char depth, char maxDepth);

MIN_MAX_NODE *createEmptyNode(NODE_TYPE type, GAME_MOVE *move, int alpha, int beta, char depth, char *maxDepth) {
    MIN_MAX_NODE *node = (MIN_MAX_NODE *) malloc(sizeof(MIN_MAX_NODE));
    if (node == NULL) return NULL;
    node->type = type;
    node->game = NULL;
    node->move = move;
    node->children = NULL;
    node->next = NULL;
    node->alpha = alpha;
    node->beta = beta;
    node->value = (type == MIN) ? SUFFICIENT_MAX : SUFFICIENT_MIN;
    node->isLeaf = isLeaf(depth, *maxDepth);
    node->depth = depth;
    return node;
}

MIN_MAX_NODE *createTreeRoot(NODE_TYPE type, CHESS_GAME *game, char *maxDepth) {
    MIN_MAX_NODE *node = (MIN_MAX_NODE *) malloc(sizeof(MIN_MAX_NODE));
    if (node == NULL) return NULL;
    node->type = type;
    node->game = copyChessGame(game);
    if (node->game == NULL) return NULL;
    node->move = NULL;
    node->children = NULL;
    node->next = NULL;
    node->alpha = INT_MIN;
    node->beta = INT_MAX;
    node->value = (type == MIN) ? SUFFICIENT_MAX : SUFFICIENT_MIN;
    node->isLeaf = false;
    node->depth = 0;
    return node;
}

void destroyNode(MIN_MAX_NODE *node) {
    if (node == NULL) return;
    destroyChessGame(node->game);
    destroyGameMove(node->move);
    free(node);
}

bool isLeaf(char depth, char maxDepth) {
    if (depth == maxDepth)
        return true;
    else
        return false;
}