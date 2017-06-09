//
// Created by okleinfeld on 6/3/2017.
//

#include "SPMainAux.h"


int checkInitializationCommand(){

    int gameLevel;
    char *userInput = (char *) calloc(SP_MAX_LINE_LENGTH, sizeof(char));
    scanf("%[^\n]%*c", userInput);

    // If command = "quit"
    if (strcmp(userInput, "quit") == 0){
        free(userInput);
        return -2;
    }

    // Parse integer and detect if in range 1-7
    if (spParserIsInt(userInput)){
        gameLevel = atoi(userInput);
        if (gameLevel >= 1 && gameLevel <= 7 ) {
            free(userInput);
            return gameLevel;
        }
        else {
            free(userInput);
            return -1;
        }
    }

    // If not in range 1-7, command is illegal
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
    else return 0;
}

SPCommand parseUserCommand(){
    char *userInput = (char *) calloc(SP_MAX_LINE_LENGTH, sizeof(char));
    scanf("%[^\n]%*c", userInput);
    SPCommand parse_command = spParserPraseLine(userInput);
    free(userInput);
    return parse_command;
}

void handleGameOverScenario(char winnerSymbol, SPFiarGame *game){

    spFiarGamePrintBoard(game);

    if (winnerSymbol == SP_FIAR_GAME_PLAYER_1_SYMBOL){
        printf(GAME_OVER_WIN);
    } else if (winnerSymbol == SP_FIAR_GAME_PLAYER_2_SYMBOL){
        printf(GAME_OVER_LOSE);
    } else{
        printf(GAME_OVER_TIE);
    }
}

int getLastColumnPlayed(SPFiarGame *game){

    if (game == NULL){
        return -1;
    }

    SPArrayList *gameStack = game->gameStack;
    if (spArrayListIsEmpty(gameStack) == true){
        return -1;
    }

    int lastColumnPlayed = spArrayListGetLast(gameStack);
    return lastColumnPlayed;
}

void performUndoMoveActions(SPFiarGame *game, int *shouldPrintBoardPointer){
    int columnComp = getLastColumnPlayed(game);
    if (columnComp == -1){
        printf(ERROR_CANNOT_UNDO);
    } else {
        spFiarGameUndoPrevMove(game);
        printf(REMOVE_COMPUTER_DISC, columnComp+1);
        int columnUser = getLastColumnPlayed(game);
        spFiarGameUndoPrevMove(game);
        printf(REMOVE_USER_DISC, columnUser+1);
        *shouldPrintBoardPointer = 1;
    }
}
