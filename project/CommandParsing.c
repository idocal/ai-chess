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
    command->addressForLoadCommand = NULL;
    command->commandArgument = -1;
    return command;
}

void resetToDefualtStateCommand(SETTING_STATE_COMMAND *command){
    if (command == NULL){
        return;
    }
    if (command->addressForLoadCommand != NULL){
        free(command->addressForLoadCommand);
    }
    command->command_name = INVALID_COMMAND;
    command->commandArgument -1;
}

void destroyStateCommand(SETTING_STATE_COMMAND *command){
    if (command == NULL){
        return;
    }
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
        commandName = INVALID_COMMAND;
    }
    return commandName;
}

int transformCommandArgFromStrToInt(char *commandArg){
    int returnVal = 0;
    char digit = commandArg[0];
    char redundantChar = commandArg[1];
    if (redundantChar != '\0'){
        returnVal = -1;
    } else if (digit >= '0' && digit <= '9'){
        returnVal = digit - 48;
    } else{
        returnVal = -1;
    }
    return returnVal;
}


SETTING_STATE_COMMAND *parseUserCommand(){
    char userCommand[MAX_COMMAND_LENGTH];
    fgets(userCommand, MAX_COMMAND_LENGTH, stdin);
    const char *del = " \t\r\n";
    char *commandNameString;
    char *commandArgument;
    char *redundantArgument;
    commandNameString = strtok(userCommand, del);
    commandArgument = strtok(NULL, del);
    redundantArgument = strtok(NULL, del);
    SETTING_STATE_COMMAND *settingCommand = createDefaultStateCommand();
    if (settingCommand == NULL){
        return NULL;
    }
    if (redundantArgument != NULL){
        return settingCommand;
    }
    settingCommand->command_name = parseStringToSettingCommandEnum(commandNameString);
    if (settingCommand->command_name == INVALID_COMMAND){
        return settingCommand;
    }
    if (settingCommand->command_name == DEFAULT ||
        settingCommand->command_name == PRINT_SETTING ||
        settingCommand->command_name == QUIT ||
        settingCommand->command_name == START) {
        if (commandArgument != NULL) {
            settingCommand->command_name = INVALID_COMMAND;
        }
    } else if (settingCommand->command_name == LOAD) {
        settingCommand->addressForLoadCommand = commandArgument;
    } else {
        settingCommand->commandArgument = transformCommandArgFromStrToInt(commandArgument);
    }
    return settingCommand;
}