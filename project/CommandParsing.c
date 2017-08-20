//
// Created by okleinfeld on 7/28/2017.
//

#include "CommandParsing.h"

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
    command->commandArgument -1;
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
        strcpy(settingCommand->addressForLoadCommand, commandArgument); // no need to convert the argument
        // if the file name is not correct will result in an error in later functions no this one
    } else { // commands with single integer argument
        settingCommand->commandArgument = transformCommandArgFromStrToInt(commandArgument);
        // function only checks if the argument is a single digit. matching range will be checked later
    }
    return settingCommand;
}
