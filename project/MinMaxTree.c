//
// Created by Ido on 8/25/17.
//

#include "MinMaxTree.h"

void loopAllPossibleMoves(MIN_MAX_NODE *node, int *maxDepth, bool isRoot, GAME_MOVE **AINextMove, bool isExpert) {
    CHESS_GAME *nodeGame = node->game;

    // expert level - allow pruning in some probability. not allowed in tree root
    // the value game->pruningThreshold defines the probability of pruning and decreases as the game progresses
    double randomNumber = (double) rand() / RAND_MAX;
    if (isExpert == true && node->depth > 0 && randomNumber <= node->game->pruningThreshold){
        return;
    }

    // Loop through the player's pieces and detect possible moves:
    for (int x = 0; x < nRows; x++) {
        for (int y = 0; y < nCols; y++) {
            char piece = matGet(nodeGame->gameBoard, x, y);
            if (pieceOwner(piece, nodeGame->currentPlayer) == 1) { // if board(x,y) is player's piece
                MATRIX *possibleMoves = piecePossibleMoves(nodeGame, piece, x, y, true);
                // Loop through the possible moves of the current piece:
                for (int i = 0; i < nRows; i++) {
                    for (int j = 0; j < nCols; j++) {
                        if (matGet(possibleMoves, i, j)){ // (i,j) is indeed a possible move
                            GAME_MOVE *nextMove = createGameMove(nodeGame, x, y, i, j);
                            MIN_MAX_NODE *childNode = createMinMaxNode(opposite(node->type), nodeGame, nextMove,
                                                                       node->alpha, node->beta, node->depth + 1,
                                                                       maxDepth);

                            if (childNode == NULL) return;
                            evaluateNode(childNode, maxDepth, isExpert);

                            if (node->type == MAX && childNode->value > node->value){
                                node->value = childNode->value;
                                node->alpha = childNode->value;
                                if (isRoot) {
                                    if (*AINextMove == NULL){
                                        *AINextMove = copyGameMove(childNode->move);
                                    }
                                    else{
                                        GAME_MOVE *tmpMove = *AINextMove;
                                        *AINextMove = copyGameMove(childNode->move);
                                        destroyGameMove(tmpMove);
                                    }
                                }
                            }

                            if (node->type == MIN && childNode->value < node->value){
                                node->value = childNode->value;
                                node->beta = childNode->value;
                                if (isRoot) {
                                    if (*AINextMove == NULL){
                                        *AINextMove = copyGameMove(childNode->move);
                                    }
                                    else{
                                        GAME_MOVE *tmpMove = *AINextMove;
                                        *AINextMove = copyGameMove(childNode->move);
                                        destroyGameMove(tmpMove);
                                    }
                                }
                            }

                            destroyNode(childNode);
                        }

                        if (node->alpha >= node->beta) break; // prune this node
                    }

                    if (node->alpha >= node->beta) break; // prune this node
                }

            }

            if (node->alpha >= node->beta) break; // prune this node
        }

        if (node->alpha >= node->beta) break; // prune this node
    }

    return;
}

void evaluateNode(MIN_MAX_NODE *node, int *maxDepth, bool isExpert) {
    CHESS_GAME *nodeGame = node->game;

    // Halting terms:
    if (isCheckMate(nodeGame)){
        node->value = (nodeGame->currentPlayer == 0) ? INT_MAX : INT_MIN;
        return;
    }

    if (isTie(nodeGame)) {
        node->value = 0;
        return;
    }

    if (node->isLeaf){
        node->value = score(nodeGame);
        return;
    }

    // Loop through all player's possible moves
    // maxDepth "d" derives O(d) space complexity
    loopAllPossibleMoves(node, maxDepth, false, NULL, isExpert);
    return;
}

GAME_MOVE *AINextMove(CHESS_GAME *game, int *maxDepth, bool isExpert) {
    char player = game->currentPlayer;
    NODE_TYPE type = (player == 1) ? MAX : MIN;
    MIN_MAX_NODE *root = createTreeRoot(type, game, maxDepth);

    if (root == NULL) return NULL;

    GAME_MOVE *AINextMove = NULL;
    loopAllPossibleMoves(root, maxDepth, true, &AINextMove, isExpert);

    destroyNode(root);
    return AINextMove;
}