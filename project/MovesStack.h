//
// Created by okleinfeld on 7/27/2017.
//

#ifndef PROJECT_MOVESSTACK_H
#define PROJECT_MOVESSTACK_H

#include "GameRepresenation.h"

/**
 * MoveStack Summary:
 *
 * This header contains definitions of the game stack
 * which is a stack data structure with each object is a game move object
 */

/**
 * Structure used to represent a game moves stack
 * the stack itself is an array of move array pointers
 * the stack is implemented thus using a circular array and it is a fixed size
 * when maximum capacity is reached the "oldest" move is forgotten (also freeing its memory)
 * (Last in First out - but First in First trashed)
 */
typedef struct game_moves_stack {
    GAME_MOVE **movesArray;
    int capacity;
    int currentSize;
    int topIndex;
} MOVES_STACK;

/**
 * Creates a new empty/default chess game and return a pointer to it.
 * Preforms all the memory allocation commands needed.
 *
 * @param capacity - the Stack's maximun capacity
 *
 * @return
 * NULL if  a memory allocation failure occurs.
 * Otherwise, a pointer to a new move stack instance is returned.
 *
 * Initiation of the object's fields:
 * moves array -> all array's cell initiated to NULL
 * capacity -> same as the functions given argument
 * currentSize -> 0
 * topIndex -> -1 (topIndex+1 always points to the next available space if there is any)
 */
MOVES_STACK* createEmptyStack(int capacity);


/**
 * Free all memory attached with the stack object
 * Including freeing all of the stack's moves objects(!!!)
 *
 * @param stack - pointer to a given stack object
 */
void destroyStack(MOVES_STACK *stack);

/**
 * Returns the pointer to the last move played
 * also pops is from the stack
 *
 * @param stack - pointer to a given stack object
 *
 * @return
 * NULL if an empty stack is given or pointer to an object represents the last move played
 */
GAME_MOVE* pop(MOVES_STACK *stack);


/**
 * Adds a new move to the top of the stack
 * if the stack's capacity is reached, an earlier move will be dropped
 *
 * @param
 * stack - pointer to a given stack object
 * gameMove - a pointer to a valid gameMover object
 */
void push(MOVES_STACK *stack, GAME_MOVE* gameMove);


/**
 * Returns the pointer to the last move played
 * without(!) performing pop, the object will stay in the stack
 *
 * @param stack - pointer to a given stack object
 *
 * @return
 * NULL if an empty stack is given or pointer to an object represents the last move played
 */
GAME_MOVE* peek(MOVES_STACK *stack);

#endif //PROJECT_MOVESSTACK_H
