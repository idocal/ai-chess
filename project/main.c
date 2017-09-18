//
// Created by okleinfeld on 9/17/17.
//

#define TOO_MANY_ARGS_ERROR "Error: Only one command line argument is allowed\n"
#define WRONG_ARG_ERROR "Error: The only allowed command line arguments are -c or -g\n"
#define GUIDING_MESSAGE_PART_1 "Calling the program with \"-c\" flag will execute the console mode\n"
#define GUIDING_MESSAGE_PART_2 "Calling the program with \"-g\" flag will execute the GUI mode\n"
#define GUIDING_MESSAGE_PART_3 "Calling the program without a flag will execute the console mode by default\n"

#include <stdio.h>
#include <string.h>
#include "mainConsole.h"
#include "mainGUI.h"

int main(int argc, char *argv[]){
    if (argc > 2){
        printf(TOO_MANY_ARGS_ERROR);
        printf(GUIDING_MESSAGE_PART_1);
        printf(GUIDING_MESSAGE_PART_2);
        printf(GUIDING_MESSAGE_PART_3);
    } else if (argc == 2){
        if (strcmp(argv[1], "-g") == 0){
            mainGui();
        } else if (strcmp(argv[1], "-c") == 0){
            mainConsole();
        } else{
            printf(WRONG_ARG_ERROR);
            printf(GUIDING_MESSAGE_PART_1);
            printf(GUIDING_MESSAGE_PART_2);
            printf(GUIDING_MESSAGE_PART_3);
        }
    } else{ // no argument at all
        mainConsole();
    }
    return 0;
}