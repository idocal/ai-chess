#include <stdio.h>
#include "GameRepresenation.h"
#include "MovesStack.h"
#include "CommandParsing.h"

int main() {
/*    CHESS_GAME *game = createEmptyGame();
    printChessGameBoard(game);
    printf("\nnow ready to start a game\n");
    initGameBoard(game);
    printChessGameBoard(game);
    CHESS_GAME *newGame = copyChessGame(game);
    destoryChessGame(game);
    printf("\nnow check that the copied game looks fine\n");
    printChessGameBoard(newGame);
    destoryChessGame(newGame);*/
/*    CHESS_GAME *game = createEmptyGame();
    initGameBoard(game);
    GAME_MOVE *move1 = createGameMove(game, 0, 0, 3, 0);
    GAME_MOVE *move2 = createGameMove(game, 0, 1, 3, 1);
    GAME_MOVE *move3 = createGameMove(game, 0, 2, 3, 2);
    GAME_MOVE *move4 = createGameMove(game, 0, 3, 3, 3);
    MOVES_STACK *stack = createEmptyStack(3);
    push(stack, move1);
    push(stack, move2);
    push(stack, move3);
    push(stack, move4);
    for (int i = 0; i < 3; ++i){
        printf("the address of the current move in place %d is %x\n", i, stack->movesArray[i]);
    }
    pop(stack);
    pop(stack);
    for (int i = 0; i < 3; ++i){
        printf("the address of the current move in place %d is %x\n", i, stack->movesArray[i]);
    }
    GAME_MOVE *move5 = createGameMove(game, 0, 4, 3, 0);
    GAME_MOVE *move6 = createGameMove(game, 0, 5, 3, 1);
    push(stack, move5);
    push(stack, move6);
    for (int i = 0; i < 3; ++i) {
        printf("the address of the current move in place %d is %x\n", i, stack->movesArray[i]);
    }
    printf("top of stack is %x\n", stack->movesArray[stack->topIndex]);
    GAME_MOVE *move7 = createGameMove(game, 0, 6, 3, 1);
    push(stack, move7);
    for (int i = 0; i < 3; ++i) {
        printf("the address of the current move in place %d is %x\n", i, stack->movesArray[i]);
    }
    printf("top of stack is %x\n", stack->movesArray[stack->topIndex]);
    return 0;*/
    SETTING_STATE_COMMAND *command = parseUserCommand();
    printf("command is invalid ?? %d\n", command->command_name == INVALID_COMMAND);
    destroyStateCommand(command);
    SETTING_STATE_COMMAND *command2 = parseUserCommand();
    printf("command is invalid ?? %d\n", command->command_name == INVALID_COMMAND);
    destroyStateCommand(command);
    SETTING_STATE_COMMAND *command3 = parseUserCommand();
    printf("command is invalid ?? %d\n", command->command_name == INVALID_COMMAND);
    destroyStateCommand(command);
}