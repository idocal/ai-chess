//
// Created by Ido on 8/25/17.
//

#include "MinMaxTree.h"

TERMINATING_CONDITION isTerminalNode(MIN_MAX_NODE *node){
    CHESS_GAME *nodeGame = node->game;

    // Halting terms:

    // Game is not over but node is a leaf
    if (node->isLeaf){
        return NODE_IS_LEAF;
    }

    // Game is over due to a tie
    if (isTie(nodeGame)) {
        node->value = 0;
        return GAME_OVER_TIE;
    }

    // Game is over due to a victory
    if (isCheckMate(nodeGame)){
        return GAME_OVER_CHECK_MATE;
    }


    // otherwise no terminating condition
    return NOT_TERMINATING;
}

void updateScoreForTerminatingNode(MIN_MAX_NODE *node, TERMINATING_CONDITION stopReason, bool isExpert){
    CHESS_GAME *nodeGame = node->game;
    srand(time(NULL)); // set seed for random number generation

    if (stopReason == GAME_OVER_CHECK_MATE){
        // the winner is the opponent of the current player
        // if the current player is player 0 then the winner is player 1 which scores in negative values
        node->value = (nodeGame->currentPlayer == 0) ? INT_MIN : INT_MAX;


    } else if (stopReason == GAME_OVER_TIE){
        // in case of a tie give a neutral score of zero
        node->value = 0;


    } else {
        // node is a leaf. heuristic scoring function depends on game level

        if (isExpert){
            node->value = score(nodeGame);

        } else {
            node->value = expertScore(nodeGame);
        }

    }
}

void minMaxAlphaBetaAlgorithm(MIN_MAX_NODE *node, int *maxDepth, bool isExpert, GAME_MOVE **AINextMove, bool isRoot) {
    CHESS_GAME *nodeGame = node->game;

    TERMINATING_CONDITION stopCondition = isTerminalNode(node);
    if (stopCondition == NODE_IS_LEAF || stopCondition == GAME_OVER_CHECK_MATE || stopCondition == GAME_OVER_TIE) { // stopping criterion is reached
        updateScoreForTerminatingNode(node, stopCondition, isExpert);
        return;
    }

    // Enter recursion
    // Loop through the player's pieces and detect possible moves:
    for (int x = 0; x < nRows; x++) {
        for (int y = 0; y < nCols; y++) {
            char piece = matGet(nodeGame->gameBoard, x, y);

            if (pieceOwner(piece, nodeGame->currentPlayer) == 1) { // if board(x,y) is player's piece

                MATRIX *possibleMoves = piecePossibleMoves(nodeGame, piece, x, y, true);

                // Loop through the possible moves of the current piece:
                for (int i = 0; i < nRows; i++) {
                    for (int j = 0; j < nCols; j++) {
                        if (matGet(possibleMoves, i, j)) { // (i,j) is indeed a possible move
                            GAME_MOVE *nextMove = createGameMove(nodeGame, x, y, i, j);

                            // check memory error
                            if (nextMove == NULL){
                                destroyGameMove(nextMove);
                                continue; // move to next possible move
                            }

                            MIN_MAX_NODE *childNode = createMinMaxNode(opposite(node->type), nodeGame, nextMove, node->alpha, node->beta, node->depth + 1, maxDepth);

                            // check memory error
                            if (childNode == NULL){
                                destroyGameMove(nextMove);
                                continue; // destroy move object and iterate to next possible move
                            }

                            // compute childNode score recursively
                            minMaxAlphaBetaAlgorithm(childNode, maxDepth, isExpert, AINextMove, false);

                            if (node->type == MAX_NODE){

                                if(node->value < childNode->value){
                                    node->value = childNode->value;

                                    // need to also update the nextAIMove Object if we are in root
                                    if (isRoot){

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

                                if (node->alpha < node->value){
                                    node->alpha = node->value;
                                }
                            }

                            if (node->type == MIN_NODE) {

                                if(childNode->value < node->value){
                                    node->value = childNode->value;

                                    // need to also update the nextAIMove Object if we are in root
                                    if (isRoot){

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

                                if (node->beta > node->value){
                                    node->beta = node->value;
                                }
                            }

                            destroyNode(childNode);
                            destroyGameMove(nextMove);

                            if (isExpert){
                                int randomInt = rand(); // create a random integer between 0 and RAND_MAX value
                                double randomProb = (double) randomInt / RAND_MAX; // convert into probability dividing by RAND_MAX

                                if (node->beta <= node->alpha || randomProb <= nodeGame->pruningThreshold){
                                    // if alpha-beta pruning condition applies or the random probability is small enough
                                    matDestroy(possibleMoves);
                                    return;
                                }

                            } else {
                                if (node->beta <= node->alpha) { // alpha-beta pruning terminates the call
                                    matDestroy(possibleMoves);
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

GAME_MOVE *AINextMove(CHESS_GAME *game, int *maxDepth, bool isExpert) {
    char player = game->currentPlayer;
    NODE_TYPE type = (opponent(player) == 0) ? MAX_NODE : MIN_NODE;
    MIN_MAX_NODE *root = createTreeRoot(type, game, maxDepth);

    if (root == NULL) return NULL;

    GAME_MOVE *AINextMove = NULL;
    minMaxAlphaBetaAlgorithm(root, maxDepth, isExpert, &AINextMove, true);

    destroyNode(root);
    return AINextMove;
}