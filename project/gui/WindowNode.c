//
// Created by okleinfeld on 9/10/17.
//

#include "WindowNode.h"


WINDOW_NODE *createWindowNode(GENERIC_WINDOW *window){
    WINDOW_NODE *node = (WINDOW_NODE *) malloc(sizeof(WINDOW_NODE));
    if (node == NULL){
        return NULL;
    }
    node->window = window;
    node->next = NULL;
    return node;
}

void destroyWindowNode(WINDOW_NODE *node){
    if (node == NULL){
        return;
    }
    destroyWindow(node->window);
    free(node);
}