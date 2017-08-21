//
// Created by okleinfeld on 7/28/2017.
//

#include "CommandParsing.h"


GAME_STATE_COMMAND *createDefaultGameCommand(){
    GAME_STATE_COMMAND *command = (GAME_STATE_COMMAND *) malloc(sizeof(GAME_STATE_COMMAND));
    if (command == NULL) {
        return NULL;
    }
    command->command_name = INVALID_GAME_COMMAND;
    command->move = NULL;
    command->filename = (char *) calloc(MAX_COMMAND_LENGTH, sizeof(char));
    command->x = -1;
    command->y = -1;
}

void destroyGameCommand(GAME_STATE_COMMAND *command){
    if (command == NULL){
        return;
    }
    free(command->filename);
    //important!! do not free the memory of MOVE object as it is probably being added to
    // the game stack and memory allocation is still needed. only the pointer will get free

    free(command);
}


GAME_STATE_COMMAND_NAME parseStringToGameCommandEnum(char *commandString){
    SETTING_STATE_COMMAND_NAME commandName;
    if (commandString == NULL){
        commandName = INVALID_GAME_COMMAND;
    } else if (strcmp(commandString, "move") == 0){
        commandName = MOVE;
    } else if (strcmp(commandString, "save") == 0){
        commandName = SAVE;
    } else if (strcmp(commandString, "undo") == 0){
        commandName = UNDO;
    } else if (strcmp(commandString, "reset") == 0){
        commandName = RESET;
    } else if (strcmp(commandString, "quit") == 0){
        commandName = QUIT_GAME;
    } else if (strcmp(commandString, "get_moves") == 0){
        commandName = GET_MOVES;
    } else {
        commandName = INVALID_GAME_COMMAND; // any other string will result in INVALID GAME COMMAND output
    }
    return commandName;
}

SETTING_STATE_COMMAND *createDefaultStateCommand(){
    SETTING_STATE_COMMAND *command = (SETTING_STATE_COMMAND *) malloc(sizeof(SETTING_STATE_COMMAND));
    if (command == NULL){
        return NULL;
    }
    command->command_name = INVALID_COMMAND;
    command->addressForLoadCommand = (char *) calloc(MAX_COMMAND_LENGTH, sizeof(char));
    command->commandArgument = -1;
    return command;
}

void resetToDefualtStateCommand(SETTING_STATE_COMMAND *command){
    if (command == NULL){
        return;
    }

    // No need to free addressForLoadCommand string. it wasn't allocated by the programmer!
    // was allocated by the OS as part of stdin creation
    free(command->addressForLoadCommand);
    command->addressForLoadCommand = (char *) calloc(MAX_COMMAND_LENGTH, sizeof(char));
    command->command_name = INVALID_COMMAND;
    command->commandArgument = -1;
}

void destroyStateCommand(SETTING_STATE_COMMAND *command){
    if (command == NULL){
        return;
    }
    free(command->addressForLoadCommand);// free the address to file string memory;
    free(command);
}

SETTING_STATE_COMMAND_NAME parseStringToSettingCommandEnum(char *commandString){
    SETTING_STATE_COMMAND_NAME commandName;
    if (commandString == NULL){
        commandName = INVALID_COMMAND;
    } else if (strcmp(commandString, "game_mode") == 0){
        commandName = GAME_MODE;
    } else if (strcmp(commandString, "difficulty") == 0){
        commandName = DIFFICULTY;
    } else if (strcmp(commandString, "user_color") == 0){
        commandName = USER_COLOR;
    } else if (strcmp(commandString, "load") == 0){
        commandName = LOAD;
    } else if (strcmp(commandString, "default") == 0){
        commandName = DEFAULT;
    } else if (strcmp(commandString, "print_setting") == 0) {
        commandName = PRINT_SETTING;
    } else if (strcmp(commandString, "quit") == 0) {
        commandName = QUIT;
    } else if (strcmp(commandString, "start") == 0) {
        commandName = START;
    } else {
        commandName = INVALID_COMMAND; // any other string will result in INVALID COMMAND output
    }
    return commandName;
}

int transformCommandArgFromStrToInt(char *commandArg){
    int returnVal = 0;
    char digit = commandArg[0];
    char redundantChar = commandArg[1];
    if (redundantChar != '\0'){ // if more than 1 char - wrong input
        returnVal = -1;
    } else if (digit >= '0' && digit <= '9'){
        returnVal = digit - 48; // return corresponding integer value
    } else{ // just single char but doesn't represent a digit
        returnVal = -1;
    }
    return returnVal;
}


SETTING_STATE_COMMAND *parseUserSettingCommand(){
    char userCommand[MAX_COMMAND_LENGTH];
    fgets(userCommand, MAX_COMMAND_LENGTH, stdin); // read input to buffer
    const char *del = " \t\r\n";
    char *commandNameString; // command name
    char *commandArgument; // argument
    char *redundantArgument; // extra argument (NULL for valid commands)
    commandNameString = strtok(userCommand, del);
    commandArgument = strtok(NULL, del);
    redundantArgument = strtok(NULL, del);
    SETTING_STATE_COMMAND *settingCommand = createDefaultStateCommand();
    if (settingCommand == NULL){
        return NULL;
    }
    if (redundantArgument != NULL){ // more than two words - command is error
        return settingCommand; // the default value is "INVALID_COMMAND"
    }
    settingCommand->command_name = parseStringToSettingCommandEnum(commandNameString);
    if (settingCommand->command_name == INVALID_COMMAND){ // name of command is not legal
        return settingCommand; // again no need to change, command name is already invalid command
    }
    if (settingCommand->command_name == DEFAULT ||
        settingCommand->command_name == PRINT_SETTING ||
        settingCommand->command_name == QUIT ||
        settingCommand->command_name == START) {
        // all the command names that doesn't have another argument except for their name
        if (commandArgument != NULL) { // in this case, even a single argument is redundant
            settingCommand->command_name = INVALID_COMMAND; // change name to INVALID_COMMAND
        }
    } else if (settingCommand->command_name == LOAD) {
        if (commandArgument == NULL){ // no address argument was specified
            settingCommand->command_name = INVALID_COMMAND;
        } else{
            strcpy(settingCommand->addressForLoadCommand, commandArgument); // no need to convert the argument
        }// if the file name is not correct will result in an error in later functions no this one
    } else { // commands with single integer argument
        settingCommand->commandArgument = transformCommandArgFromStrToInt(commandArgument);
        // function only checks if the argument is a single digit. matching range will be checked later
    }
    return settingCommand;
}

GAME_STATE_COMMAND *parseUserGameCommand() {
    char userCommand[MAX_COMMAND_LENGTH];
    fgets(userCommand, MAX_COMMAND_LENGTH, stdin); // read input to buffer
    const char *del = " \t\r\n";
    char *commandNameString; // command name
    char *firstArg; // first argument (specific command dependent)
    char *secondArg; // second argument (will be the string "to" in case of MOVE command. otherwise has to be NULL
    char *thirdArg; // third argument (will be <i,j> in case of a MOVE command. otherwise has to be NULL
    char *fourthArg; //extra argument (NULL for valid commands)
    commandNameString = strtok(userCommand, del);
    firstArg = strtok(NULL, del);
    secondArg = strtok(NULL, del);
    thirdArg = strtok(NULL, del);
    fourthArg = strtok(NULL, del);
    GAME_STATE_COMMAND *gameCommand = createDefaultGameCommand();
    if (gameCommand == NULL){
        return NULL;
    }
    if (fourthArg != NULL){ // more than 4 words - command is error anyway
        return gameCommand; // the default value is "INVALID_COMMAND"
    }
    gameCommand->command_name = parseStringToGameCommandEnum(commandNameString);
    if (gameCommand->command_name == INVALID_GAME_COMMAND){ // name of command is not legal
        return gameCommand; // again no need to change, command name is already invalid command
    }
    if (gameCommand->command_name == UNDO ||
        gameCommand->command_name == RESET ||
        gameCommand->command_name == QUIT_GAME){
        // all the command names that doesn't have another argument except for their name
        if (firstArg != NULL) { // in this case, even a single argument is redundant
            gameCommand->command_name = INVALID_GAME_COMMAND; // change name to INVALID_COMMAND
        }
    } else if (gameCommand->command_name == SAVE) {
        if (firstArg == NULL){ // file address argument wasn't supplied at all
            gameCommand->command_name = INVALID_GAME_COMMAND;
        } else{
            strcpy(gameCommand->filename, firstArg); // no need to convert the argument
        }// if the file name is not correct will result in an error in later functions no this one
    } else if (gameCommand->command_name == GET_MOVES){
        if (secondArg != NULL){
            gameCommand->command_name = INVALID_GAME_COMMAND; // "GET_MOVES" command that has more than one string after is illegal
        } else if (checkValidityOfMovePositionString(firstArg) == 0){
            gameCommand->command_name = INVALID_GAME_COMMAND; // the argument for the command is not valid or not valid position
        } else{
            char get_move_x[2];
            char get_move_y[2];
            get_move_x[0] = firstArg[1] -1;
            get_move_y[0] = firstArg[3] -16 -1;
            get_move_x[1] = '\0';
            get_move_y[1] = '\0';
            gameCommand->x = transformCommandArgFromStrToInt(get_move_x);
            gameCommand->y = transformCommandArgFromStrToInt(get_move_y);
            // returned arguments are already 0-based!
            // not checking if the board position has a user's piece on it, just if it is a valid board position
        }
    } else { // MOVE_TO Command
        if (checkValidityOfMovePositionString(firstArg) == 0
            || strcmp(secondArg, "to") != 0
            || checkValidityOfMovePositionString(thirdArg) == 0){ // the string is not valid / not right format / not right positions
            gameCommand->command_name = INVALID_GAME_COMMAND;
        } else{
            char move_source_x[2];
            char move_source_y[2];
            char move_dest_x[2];
            char move_dest_y[2];
            move_source_x[0] = firstArg[1] -1;
            move_source_y[0] = firstArg[3] -16 -1;
            move_dest_x[0] = thirdArg[1] -1;
            move_dest_y[0] = thirdArg[3] -16 -1;
            move_source_x[1] = '\0';
            move_source_y[1] = '\0';
            move_dest_x[1] = '\0';
            move_dest_y[1] = '\0';
            GAME_MOVE *move = createGameMoveWithoutGame(transformCommandArgFromStrToInt(move_source_x),
                                      transformCommandArgFromStrToInt(move_source_y),
                                      transformCommandArgFromStrToInt(move_dest_x),
                                      transformCommandArgFromStrToInt(move_dest_y));
            gameCommand->move = move;
        }
    }
    return gameCommand;
}

int checkValidityOfMovePositionString(char *movePosSting){
    if (movePosSting == NULL){
        return 0;
    }
    if (*movePosSting != '<'){
        return 0;
    }
    movePosSting++;
    if (*movePosSting < '1' || *movePosSting > '8'){
        return 0;
    }
    movePosSting++;
    if (*movePosSting != ','){
        return 0;
    }
    movePosSting++;
    if (*movePosSting < 'A' || *movePosSting > 'H'){
        return 0;
    }
    movePosSting++;
    if (*movePosSting != '>'){
        return 0;
    }
    movePosSting++;
    if (*movePosSting != '\0'){ //the string contains more characters after <x,y>
        return 0;
    }
    return 1;
}

