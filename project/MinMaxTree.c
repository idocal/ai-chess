//
// Created by Ido on 8/25/17.
//

#include "MinMaxTree.h"
#include "Scoring.h"
#include "GameStates.h"

#define opposite(type) ((type == MIN) ? MAX : MIN)
#define opponent(player) ((char) (1 - player))


MIN_MAX_NODE *createChildrenEmptyNodesList(MIN_MAX_NODE *parent, char *maxDepth) {
    MIN_MAX_NODE *head = NULL;
    MIN_MAX_NODE *current = head;
    CHESS_GAME *game = parent->game;
    MATRIX *board = game->gameBoard;
    NODE_TYPE type = parent->type;
    int alpha = parent->alpha;
    int beta = parent->beta;
    char player = game->currentPlayer;
    char depth = parent->depth;

    for (int x = 0; x < nRows; x++) {
        for (int y = 0; y < nCols; y++) {

            char piece = matGet(board, x, y);
            if (pieceOwner(piece, player) == 1) {
                MATRIX *possibleMoves = getPossibleMoves(game, x, y);
                if (possibleMoves == NULL) return NULL;

                for (int i = 0; i < nRows; i++) {
                    for (int j = 0; j < nCols; j++) {

                        char isPossible = matGet(possibleMoves, i, j);
                        if (isPossible) {
                            GAME_MOVE *move = createGameMove(game, x, y, i, j);
                            if (move == NULL) return  NULL;

                            MIN_MAX_NODE *node = createEmptyNode(opposite(type), move, alpha, beta, depth+1, maxDepth);
                            if (node == NULL) return NULL;

                            if (head == NULL) {
                                head = node;
                            } else {
                                current->next = node;
                                current = current->next;
                            }
                        }

                    }
                }

                matDestroy(possibleMoves);
            }

        }
    }


}

int evaluateNode(MIN_MAX_NODE *node, CHESS_GAME *game, char *maxDepth) {

    if (node->alpha >= node->beta){
        return 0;
    }

    node->game = copyChessGame(game);
    if (node->game == NULL) return -1;

    CHESS_GAME *nodeGame = node->game;

    nodeGame->currentPlayer = opponent(nodeGame->currentPlayer); // switch turns
    if (node->move != NULL) performMove(game, node->move);

    if (isCheckMate(game)){
        node->value = (game->currentPlayer == 0) ? INT_MAX : INT_MIN;
        return 1;
    }

    if (isTie(game)) {
        node->value = 0;
        return 1;
    }

    if (node->isLeaf){
        node->value = score(game);
        return 1;
    }

    node->children = createChildrenEmptyNodesList(node, maxDepth);
    if (node->children == NULL) return -1;
    MIN_MAX_NODE *currentChild = node->children;
    int nodeValue = node->value;

    while (currentChild != NULL){
        int evalResult = evaluateNode(currentChild, nodeGame, maxDepth);
        if (evalResult == 1){
            if (node->type == MAX && currentChild->value > nodeValue){
                node->value = currentChild->value;
                node->alpha = currentChild->value;
            }

            if (node->type == MIN && currentChild->value < nodeValue){
                node->value = currentChild->value;
                node->beta = currentChild->value;
            }
        }
        MIN_MAX_NODE *nextChild = currentChild->next;
        destroyNode(currentChild);
        currentChild = nextChild;
    }

    return 1;
}

GAME_MOVE *AINextMove(CHESS_GAME *game, char *maxDepth) {
    char player = game->currentPlayer;
    NODE_TYPE type = (player == 1) ? MAX : MIN;
    MIN_MAX_NODE *root = createTreeRoot(type, game, maxDepth);

    if (root == NULL) return NULL;

    root->children = createChildrenEmptyNodesList(root, maxDepth);
    if (root->children == NULL) return NULL;

    GAME_MOVE *AINextMove = NULL;

    MIN_MAX_NODE *currentChild = root->children;
    int nodeValue = root->value;

    while (currentChild != NULL){
        int evalResult = evaluateNode(currentChild, game, maxDepth);
        if (evalResult == 1){
            if (root->type == MAX && currentChild->value > nodeValue){
                root->value = currentChild->value;
                root->alpha = currentChild->value;
                if (AINextMove == NULL) {
                    AINextMove = copyGameMove(currentChild->move);
                } else {
                    destroyGameMove(AINextMove);
                    AINextMove = copyGameMove(currentChild->move);
                }
            }

            if (root->type == MIN && currentChild->value < nodeValue){
                root->value = currentChild->value;
                root->beta = currentChild->value;
                if (AINextMove == NULL) {
                    AINextMove = copyGameMove(currentChild->move);
                } else {
                    destroyGameMove(AINextMove);
                    AINextMove = copyGameMove(currentChild->move);
                }
            }
        }
        MIN_MAX_NODE *nextChild = currentChild->next;
        destroyNode(currentChild);
        currentChild = nextChild;
    }

    destroyNode(root);
    return AINextMove;
}