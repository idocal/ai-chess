//
// Created by Ido on 8/25/17.
//

#include "MinMaxTree.h"
#include "Scoring.h"
#include "GameStates.h"

void loopAllPossibleMoves(MIN_MAX_NODE *node, int *maxDepth, bool isRoot, GAME_MOVE **AINextMove) {
    CHESS_GAME *nodeGame = node->game;

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

                            evaluateNode(childNode, maxDepth);

                            if (node->type == MAX && childNode->value > node->value){
                                node->value = childNode->value;
                                node->alpha = childNode->value;
                                if (isRoot) *AINextMove = childNode->move;
                            }

                            if (node->type == MIN && childNode->value < node->value){
                                node->value = childNode->value;
                                node->beta = childNode->value;
                                if (isRoot) *AINextMove = childNode->move;
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

void evaluateNode(MIN_MAX_NODE *node, int *maxDepth) {
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
    loopAllPossibleMoves(node, maxDepth, false, NULL);
    return;
}

GAME_MOVE *AINextMove(CHESS_GAME *game, int *maxDepth) {
    char player = game->currentPlayer;
    NODE_TYPE type = (player == 1) ? MAX : MIN;
    MIN_MAX_NODE *root = createTreeRoot(type, game, maxDepth);

    if (root == NULL) return NULL;

    GAME_MOVE *AINextMove = NULL;
    loopAllPossibleMoves(root, maxDepth, true, &AINextMove);

    return AINextMove;
}