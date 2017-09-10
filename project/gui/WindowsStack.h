//
// Created by okleinfeld on 9/10/17.
//

#ifndef PROJECT_WINDOWSSTACK_H
#define PROJECT_WINDOWSSTACK_H

#include "WindowNode.h"

/**
 * WindowsStack Summary:
 *
 * This header contains definitions of the windows stack
 * which is a stack data structure with each object is a Gerneric Window object
 */

/**
 * Structure used to represent a windows stack
 * the stack is implemented thus using a Linked list interface
 */
typedef struct windows_stack {
    WINDOW_NODE *head;
} WINDOWS_STACK;



/**
 * creates a new window stack. head pointer is null and current size will be zero
 *
 * @return a pointer to a new empty windows stack
 */

WINDOWS_STACK* createEmptyWindowsStack();


/**
 * frees the memory associated with the given stack object
 * including the memory associated with the window nodes and the windows themselves
 *
 * @param stack
 */

void destroyWindowsStack(WINDOWS_STACK *stack);

/**
 * pops from the head of the stack
 *
 * @param stack s
 * @return a pointer to the generic window object itself rather than the window node object
 */

GENERIC_WINDOW* popHeadWindow(WINDOWS_STACK *stack);

/**
 * add a new window node at the head of the given stack
 * performs the building of the window node object
 *
 *
 * @param stack
 * @param currentWindow
 */


void pushNewWindow(WINDOWS_STACK *stack, GENERIC_WINDOW* currentWindow);


#endif //PROJECT_WINDOWSSTACK_H
