//
// Created by Ido on 5/30/17.
//

#include "SPMiniMax.h"
#include <stdio.h>

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

void generateChildrenNodes(node *root, bool *memoryFault, int maxDepth) {
    if (root == NULL){
        return;
    }
    if (root->isLeaf || *memoryFault) {
        return;
    }

    for (int i=0; i<7; i++) {
        if (spFiarGameIsValidMove(root->game, i)) {
            root->children[i] = createNode(root->game, root->depth+1, i, maxDepth);
            if (root->children[i] == NULL){
                *memoryFault = true;
            }
        }
    }

    for (int i=0; i<7; i++) {
        if (root->children[i] != NULL) {
            generateChildrenNodes(root->children[i], memoryFault, maxDepth);
        }
    }
}

node* generateTree(SPFiarGame* game, int maxDepth) {
    if (game == NULL) {
        return NULL;
    }

    node* root = generateTreeRoot(game);
    if (root == NULL) {
        return NULL;
    }

    bool memoryFault = false;
    generateChildrenNodes(root, &memoryFault, maxDepth);

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
        int *gameHistogram = (int *) calloc(9, sizeof(int));
        if (gameHistogram == NULL){
            printf("Error: computeScore has failed\n");
            return;
        }
        gameHistogram += 4;
        gameHistogram = computeScoreHistogram(nodePointer->game, gameHistogram);
        nodePointer->score = calculateScoringFunction(gameHistogram);
        free(gameHistogram - 4);
        return;
    }
    if (optimum == MAX_NODE){
        OPTIMUM childOptimum = MIN_NODE;
        int maxScore = -10000;
        for (int i=0; i<7; i++){
            if (nodePointer->children[i] != NULL) {
                computeScore(nodePointer->children[i], childOptimum);
                int childScore = nodePointer->children[i]->score;
                if (childScore > maxScore) {
                    maxScore = childScore;
                }
            }
        }
        nodePointer->score = maxScore;
    }
    else{
        OPTIMUM childOptimum = MAX_NODE;
        int minScore = 10000;
        for (int i=0; i<7; i++){
            if (nodePointer->children[i] != NULL) {
                computeScore(nodePointer->children[i], childOptimum);
                int childScore = nodePointer->children[i]->score;
                if (childScore < minScore) {
                    minScore = childScore;
                }
            }
        }
        nodePointer->score = minScore;
    }
}

void destroyTreeNode(node *treeNode){
    if (treeNode->isLeaf){
        nodeDestroy(treeNode);
    }
    else{
        for (int i=0; i < 7; i++){
            node *childNode = treeNode->children[i];
            if (childNode != NULL){
                destroyTreeNode(childNode);
            }
        }
        nodeDestroy(treeNode);
    }
}

int spMinimaxSuggestMove(SPFiarGame* currentGame, unsigned int maxDepth) {
    node *root = generateTree(currentGame, maxDepth);
    if (root == NULL) {
        return -99;
    }
    if (currentGame->currentPlayer == SP_FIAR_GAME_PLAYER_1_SYMBOL){
        computeScore(root, MAX_NODE);
    }
    else{
        computeScore(root, MIN_NODE);
    }
    int rootScore = root->score;
    int suggestMove = -1;
    for (int i=0; i<7; i++) {
        if (root->children[i] == NULL){
            continue;
        }
        else {
            if (root->children[i]->score == rootScore) {
                suggestMove = i;
                break;
            }
        }
    }
    destroyTreeNode(root);
    return suggestMove;
}
