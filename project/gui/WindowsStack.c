//
// Created by okleinfeld on 9/10/17.
//

#include "WindowsStack.h"

WINDOWS_STACK* createEmptyWindowsStack(){
    WINDOWS_STACK *stack = (WINDOWS_STACK *) malloc(sizeof(WINDOWS_STACK));
    if (stack == NULL){
        return NULL;
    }
    stack->head = NULL;
    return stack;
}

void destroyWindowsStack(WINDOWS_STACK *stack) {
    if (stack == NULL) {
        return;
    }
    while (stack->head != NULL){
        WINDOW_NODE *nextNode = stack->head->next;
        destroyWindowNode(stack->head);
        stack->head = nextNode;
    }
    free(stack);
}

void popHeadWindow(WINDOWS_STACK *stack){
    if (stack == NULL || stack->head == NULL){
        return;
    }
    WINDOW_NODE *headWindow = stack->head;
    stack->head = stack->head->next;
    destroyWindowNode(headWindow);
}

void pushNewWindow(WINDOWS_STACK *stack, GENERIC_WINDOW* currentWindow){
    if (stack == NULL || currentWindow == NULL) {
        return;
    }
    WINDOW_NODE *window_node = createWindowNode(currentWindow);
    if (window_node == NULL) {
        return;
    }
    if (stack->head == NULL) { // no nodes in the stack
        stack->head = window_node;
    } else { // push to the head of the stack
        window_node->next = stack->head;
        stack->head = window_node;
    }
}