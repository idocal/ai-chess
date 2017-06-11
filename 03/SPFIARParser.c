//
// Created by okleinfeld on 5/17/2017.
//

#include "SPFIARParser.h"

bool spParserIsInt(const char* str){
    char first_c = *str;
    if (first_c == '-') {str++;}
    while (*str != '\0'){
        int ascii_val = (int) *str;
        if (ascii_val >= 48 && ascii_val <= 57){
            str++;
        }
        else{
            return false;
        }
    }
    return true;
}

SPCommand spParserPraseLine(const char* str){
    char string[SP_MAX_LINE_LENGTH];
    strcpy(string, str);
    SPCommand parse_command;
    const char *del = " \t\r\n";
    char *command_string;
    command_string = strtok(string, del);
    SP_COMMAND command = spParseCommandToEnum(command_string);
    parse_command.cmd = command;

    char *second_arg = strtok(NULL, del);
    char *third_arg = strtok(NULL, del);

    if (
            third_arg != NULL ||
            (parse_command.cmd != SP_ADD_DISC && second_arg != NULL)
        ) {
        parse_command.cmd = SP_INVALID_LINE;
        parse_command.validArg = false;
        parse_command.arg = -1;

    }  else if (parse_command.cmd == SP_ADD_DISC){
        bool user_arg_is_int = spParserIsInt(second_arg);
        if (user_arg_is_int == true){
            parse_command.validArg = true;
            parse_command.arg = atoi(second_arg);
        }
        else{
            parse_command.validArg = false;
        }
    }
    return parse_command;
}

SP_COMMAND spParseCommandToEnum(char *command){
    SP_COMMAND enum_object_command;
    if (command == NULL){
        enum_object_command = SP_INVALID_LINE;
    } else if (strcmp(command, "undo_move") == 0){
        enum_object_command = SP_UNDO_MOVE;
    } else if (strcmp(command, "add_disc") == 0){
        enum_object_command = SP_ADD_DISC;
    } else if (strcmp(command, "suggest_move") == 0){
        enum_object_command = SP_SUGGEST_MOVE;
    } else if (strcmp(command, "quit") == 0){
        enum_object_command = SP_QUIT;
    } else if (strcmp(command, "restart_game") == 0){
        enum_object_command = SP_RESTART;
    } else{
        enum_object_command = SP_INVALID_LINE;
    }
    return enum_object_command;
}
