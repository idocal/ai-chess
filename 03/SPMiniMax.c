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