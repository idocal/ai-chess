//
// Created by okleinfeld on 6/3/2017.
//

#include "SPMainAux.h"


int checkInitializationCommand(){
    int gameLevel;
    char *userInput = calloc(1024, sizeof(char));
    gets(userInput);
    if (strcmp(userInput, "quit") == 0){
        free(userInput);
        return -2;
    }
    if (spParserIsInt(userInput)){
        gameLevel = atoi(userInput);
        if (gameLevel >= 1 && gameLevel <= 7 ){
            free(userInput);
            return gameLevel;
        }
        else{
            free(userInput);
            return -1;
        }
    }
    else{
        free(userInput);
        return -1;
    }
}

int checkIfAddDiskCommandIsValid(SPCommand cmd){
    if (cmd.validArg == false){
        return 0;
    }
    if (cmd.arg >= 1 && cmd.arg <= 7){
        return 1;
    }
}

SPCommand parseUserCommand(){
    char *userInput = calloc(1024, sizeof(char));
    gets(userInput);
    SPCommand parse_command = spParserPraseLine(userInput);
    free(userInput);
    return parse_command;
}

void handleGameOverScenario(char winnerSymbol, SPFiarGame *game){
    spFiarGamePrintBoard(game);
    if (winnerSymbol == SP_FIAR_GAME_PLAYER_1_SYMBOL){
        printf("Game over: you win\nPlease enter 'quit' to exit or 'restart' to start a new game!\n");
    } else if (winnerSymbol == SP_FIAR_GAME_PLAYER_2_SYMBOL){
        printf("Game over: computer wins\nPlease enter 'quit' to exit or 'restart' to start a new game!\n");
    } else{
        printf("Game over: it's a tie\nPlease enter 'quit' to exit or 'restart' to start a new game!\n");
    }
}

int getLastColumnPlayed(SPFiarGame *game){
    if (game == NULL){
        return -1;
    }
    SPArrayList *gameStack = game->gameStack;
    int *tops = game->tops;
    if (spArrayListIsEmpty(gameStack) == true){
        return -1;
    }
    int lastColumnPlayed = spArrayListGetLast(gameStack);
    return lastColumnPlayed;
}

void performUndoMoveActions(SPFiarGame *game){
    int columnComp = getLastColumnPlayed(game);
    if (columnComp == -1){
        printf("Error: cannot undo previous move!\n");
    } else{
        spFiarGameUndoPrevMove(game);
        printf("Remove disc: remove computer's disc at column %d\n", columnComp+1);
        int columnUser = getLastColumnPlayed(game);
        spFiarGameUndoPrevMove(game);
        printf("Remove disc: remove user's disc at column %d\n", columnUser+1);
    }
}