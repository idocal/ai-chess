//
// Created by okleinfeld on 7/28/2017.
//

#ifndef PROJECT_COMMANDPARSING_H
#define PROJECT_COMMANDPARSING_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX_COMMAND_LENGTH 1024

typedef enum {
    GAME_MODE,
    DIFFICULTY,
    USER_COLOR,
    LOAD,
    DEFAULT,
    PRINT_SETTING,
    QUIT,
    START,
    INVALID_COMMAND,
} SETTING_STATE_COMMAND_NAME;

typedef struct setting_state_command {
    SETTING_STATE_COMMAND_NAME command_name;
    int commandArgument;
    char *addressForLoadCommand;
} SETTING_STATE_COMMAND;

SETTING_STATE_COMMAND *createDefaultStateCommand();

void resetToDefualtStateCommand(SETTING_STATE_COMMAND *command);

void destroyStateCommand(SETTING_STATE_COMMAND *command);

SETTING_STATE_COMMAND *parseUserCommand();

SETTING_STATE_COMMAND_NAME parseStringToSettingCommandEnum(char *string);

int transformCommandArgFromStrToInt(char *commandArg);

#endif //PROJECT_COMMANDPARSING_H
