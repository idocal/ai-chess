//
// Created by okleinfeld on 7/27/2017.
//

#include "MovesStack.h"

MOVES_STACK* createEmptyStack(int capacity){
    if (capacity <= 0){
        return NULL;
    }
    MOVES_STACK *stack = (MOVES_STACK *) malloc(sizeof(MOVES_STACK));
    if (stack == NULL){
        return NULL;
    }
    // allocating the actual stack Array for game move objects
    stack->movesArray = (GAME_MOVE **) malloc(capacity * sizeof(GAME_MOVE *));
    if (stack->movesArray == NULL){
        free(stack);
        return NULL;
    }
    // initiating values as specified in the headers description
    for (int i = 0; i < capacity; ++i){
        stack->movesArray[i] = NULL;
    }
    stack->capacity = capacity;
    stack->currentSize = 0;
    stack->topIndex = -1;
    return stack;
}

void destroyStack(MOVES_STACK *stack){
    if (stack == NULL){
        return;
    }
    for (int i = 0; i < stack->capacity; ++i){
        destroyGameMove(stack->movesArray[i]); // before freeing the stack it self, first free every object!
    }
    free(stack);
}

GAME_MOVE* pop(MOVES_STACK *stack){
    if (stack == NULL || stack->currentSize == 0){
        return NULL;
    }
    GAME_MOVE *topMove = stack->movesArray[stack->topIndex];
    stack->movesArray[stack->topIndex] = NULL; // location now has null value not former (popped) pointer value
    stack->currentSize--;
    if (stack->currentSize == 0){
        stack->topIndex = -1;
    } else {
        stack->topIndex = (stack->topIndex - 1) % stack->capacity;
        if (stack->topIndex < 0){ // "%" operator is remainder not modulo like in python
            stack->topIndex += stack->capacity; // a workaround this is to add the capacity - resulting in a positive value again
        }
    }
    return topMove;
}

void push(MOVES_STACK *stack, GAME_MOVE* gameMove){
    if (stack == NULL || gameMove == NULL){
        return;
    }
    if (stack->currentSize < stack->capacity){
        stack->currentSize++;
    }
    stack->topIndex = (stack->topIndex + 1) % stack->capacity; // update the pointer to the top index
    GAME_MOVE *forgetMove = stack->movesArray[stack->topIndex];
    destroyGameMove(forgetMove); // have to free the thrashed move, will work also if the capacity is not reached and the specified value is NULL
    stack->movesArray[stack->topIndex] = gameMove;
}

GAME_MOVE* peek(MOVES_STACK *stack){
    if (stack == NULL){
        return NULL;
    } else {
        return stack->movesArray[stack->topIndex];
    }
}