//
// Created by okleinfeld on 9/10/17.
//

#ifndef PROJECT_WINDOWNODE_H
#define PROJECT_WINDOWNODE_H

#include "GenericWindow.h"


/**
 * Structure used to represent a window node
 * containing  pointers to the corresponding window object and next window on list
 */

typedef struct window_node {
    GENERIC_WINDOW *window;
    struct window_node *next;
} WINDOW_NODE;

/**
 * create new window node
 *
 * @param window
 * @return a pointer to the new Window node
 */

WINDOW_NODE *createWindowNode(GENERIC_WINDOW *window);



/**
 * frees the memory associated with the given node
 *
 * @param node
    */
void destroyWindowNode(WINDOW_NODE *node);



#endif //PROJECT_WINDOWNODE_H
