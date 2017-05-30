//
// Created by Ido on 5/30/17.
//

#include "SPMiniMax.h"

node* generateTreeRoot(SPFiarGame* game) {
    if (game == NULL) {
        return NULL;
    }

    node *root = createRoot(game);
    if (!root) {
        return NULL;
    }

    return root;
}

void generateChildrenNodes(node *root, bool *memoryFault) {
    if (root == NULL){
        return;
    }
    if (root->isLeaf || *memoryFault) {
        return;
    }

    for (int i=0; i<7; i++) {
        if (spFiarGameIsValidMove(root->game, i)) {
            root->children[i] = createNode(root->game, root->depth+1, i);
            if (root->children[i] == NULL){
                *memoryFault = true;
            }
        }
    }

    for (int i=0; i<7; i++) {
        if (root->children[i] != NULL) {
            generateChildrenNodes(root->children[i], memoryFault);
        }
    }
}

node* generateTree(SPFiarGame* game) {
    node* root = generateTreeRoot(game);
    if (root == NULL) {
        return NULL;
    }

    bool memoryFault = false;
    generateChildrenNodes(root, &memoryFault);

    if (memoryFault) {
        return NULL;
    }

    return root;
}

void computeScore(node *nodePointer, OPTIMUM optimum) {
    if (nodePointer == NULL) {
        return;
    }

    if (nodePointer->isLeaf) {
        int *gameHistogram = calloc(9, sizeof(int));
        if (gameHistogram == NULL){
            return;
        }
        gameHistogram += 4;
        gameHistogram = computeScoreHistogram(nodePointer->game->gameBoard, gameHistogram);
        nodePointer->score = calculateScoringFunction(gameHistogram);
        free(gameHistogram - 4);
        return;
    }
    if (optimum == MAX_NODE){
        OPTIMUM childOptimum = MIN_NODE;
        int maxScore = -10000;
        int maxScoreIndex = -1;
        for (int i=0; i<7; i++){
            if (nodePointer->children[i] != NULL) {
                computeScore(nodePointer->children[i], childOptimum);
                int childScore = nodePointer->children[i]->score;
                if (childScore > maxScore) {
                    maxScore = childScore;
                    maxScoreIndex = i;
                }
            }
        }
        nodePointer->score = maxScore;
    }
    else{
        OPTIMUM childOptimum = MAX_NODE;
        int minScore = 10000;
        int minScoreIndex = -1;
        for (int i=0; i<7; i++){
            if (nodePointer->children[i] != NULL) {
                computeScore(nodePointer->children[i], childOptimum);
                int childScore = nodePointer->children[i]->score;
                if (childScore < minScore) {
                    minScore = childScore;
                    minScoreIndex = i;
                }
            }
        }
        nodePointer->score = minScore;
    }


}

int spMinimaxSuggestMove(SPFiarGame* currentGame, unsigned int maxDepth) {
    node *root = generateTree(currentGame);
    if (root == NULL) {
        return NULL;
    }
    computeScore(root, MAX_NODE);
    int rootScore = root->score;
    for (int i=0; i<7; i++) {
        if (root->children[i]->score == rootScore) {
            return i;
        }
    }
}