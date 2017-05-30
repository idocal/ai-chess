//
// Created by okleinfeld on 5/17/2017.
//

#include "SPFAIRParser.h"

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

SPCommand spParserPraseLine(char* str){
    char string[1024];
    strcpy(string, str);
    SPCommand parse_command;
    const char *del = " \t\r\n";
    char *command_string;
    command_string = strtok(string, del);
    SP_COMMAND command = spParseCommandToEnum(command_string);
    parse_command.cmd = command;
    if (parse_command.cmd == SP_ADD_DISC){
        char *user_arg_str = strtok(NULL, del);
        bool user_arg_is_int = spParserIsInt(user_arg_str);
        if (user_arg_is_int == true){
            parse_command.validArg = true;
            parse_command.arg = atoi(user_arg_str);
        }
    }
    else{
        parse_command.validArg = false;
    }
    return parse_command;
}

SP_COMMAND spParseCommandToEnum(char *command){
    SP_COMMAND enum_object_command;
    if (strcmp(command, "undo_move") == 0){
        enum_object_command = SP_UNDO_MOVE;
    } else if (strcmp(command, "add_disc") == 0){
        enum_object_command = SP_ADD_DISC;
    } else if (strcmp(command, "suggest_move") == 0){
        enum_object_command = SP_SUGGEST_MOVE;
    } else if (strcmp(command, "quit") == 0){
        enum_object_command = SP_QUIT;
    } else if (strcmp(command, "restart") == 0){
        enum_object_command = SP_RESTART;
    } else{
        enum_object_command = SP_INVALID_LINE;
    }
    return enum_object_command;
}