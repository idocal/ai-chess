//
// Created by Ido on 8/13/17.
//

#include "GameAux.h"
#include "XMLLoadParser.h"
#define PRINT_INVALID_COMMAND_ERROR "Invalid command. Please try again\n"
#define PRINT_SET_ONE_PLAYER_COMMAND "Game mode is set to 1 player\n"
#define PRINT_SET_TWO_PLAYERS_COMMAND "Game mode is set to 2 players\n"
#define PRINT_WRONG_GAME_MODE_COMMAND "Wrong game mode\n"
#define PRINT_SET_NEW_DIFFICULTY "Difficulty level is changed to %d\n"
#define PRINT_WRONG_DIFFICULTY_LEVEL_ERROR "Wrong difficulty level. the value should be between 1 to 5\n"
#define PRINT_DIFFICULTY_LEVEL_WRONG_GAME_MODE "Error. You cannot define difficulty level in 2 players mode\n"
#define PRINT_USER_COLOR_WRONG_GAME_MODE "Error. You cannot define the user's color in 2 players mode\n"
#define PRINT_SET_NEW_USER_COLOR "User color is changed to %s\n"
#define PRINT_WRONG_USER_COLOR_ERROR "Wrong user color. the value should be 0 or 1"
#define PRINT_LOAD_FILE_ERROR "Eror: File doesn't exist or cannot be opened\n"
#define PRINT_GAME_SETTING_DEFAULT "Game settings are reset to default\n"
#define PRINT_EXIT_MESSAGE "Exiting...\n"

void performMove(CHESS_GAME *game, GAME_MOVE *move) {
    MATRIX *board = game->gameBoard;
    char piece = matGet(board, move->sourceRowIndex, move->sourceColIndex); // get the piece on previous cell
    matSet(board, move->sourceRowIndex, move->sourceColIndex, '_'); // fill blank on previous cell
    matSet(board, move->destRowIndex, move->destColIndex, piece); // set piece on current cell
}


int evaluateSettingStateCommand(CHESS_MATCH **matchPtr, SETTING_STATE_COMMAND *cmd) {
    SETTING_STATE_COMMAND_NAME name = cmd->command_name;
    int arg = cmd->commandArgument;
    char *addressArg = cmd->addressForLoadCommand;

    CHESS_MATCH *match = *matchPtr;

    if (name == INVALID_COMMAND) {
        printf(PRINT_INVALID_COMMAND_ERROR);
        return 0;
    }

    if (name == GAME_MODE) {
        if (arg == 1 || arg == 2) {
            match->gameMode = arg;
            (arg == 1) ? printf(PRINT_SET_ONE_PLAYER_COMMAND) : printf(PRINT_SET_TWO_PLAYERS_COMMAND);
        } else {
            printf(PRINT_WRONG_GAME_MODE_COMMAND);
        }
        return 0;
    }

    if (name == DIFFICULTY) {
        if (match->gameMode == 1) {
            if (arg >= 1 && arg <= 5) {
                printf(PRINT_SET_NEW_DIFFICULTY, arg);
                match->level = arg;
            } else {
                printf(PRINT_WRONG_DIFFICULTY_LEVEL_ERROR);
            }
        } else {
            printf(PRINT_DIFFICULTY_LEVEL_WRONG_GAME_MODE);
        }
        return 0;
    }

    if (name == USER_COLOR) {
        if (match->gameMode == 1){
            if (arg == 0){
                printf(PRINT_SET_NEW_USER_COLOR, "black");
                match->userColor = arg;
            } else if (arg == 1){
                printf(PRINT_SET_NEW_USER_COLOR, "white");
                match->userColor = arg;
            } else {
                printf(PRINT_WRONG_USER_COLOR_ERROR);
            }
        } else {
            printf(PRINT_USER_COLOR_WRONG_GAME_MODE);
        }
        return 0;
    }

    if (name == LOAD){
        CHESS_MATCH *newMatch = parseXMLGameFile(addressArg);
        if (newMatch == NULL){
            printf(PRINT_LOAD_FILE_ERROR);
            return 0;
        }
        CHESS_MATCH *destroyMatch = match;
        *matchPtr = newMatch;
        destroyChessMatch(destroyMatch);
        return 1;
    }

    if (name == DEFAULT){
        printf(PRINT_GAME_SETTING_DEFAULT);
        resetMatchSettings(match);
        return 0;
    }

    if (name == PRINT_SETTING){
        printMatchSettings(match);
        return 0;
    }

    if (name == QUIT){
        printf(PRINT_EXIT_MESSAGE);
        return 2;
    }

    if (name == START){
        initGameBoard(match->game);
        return 1;
    }

    return -1; // this should not happen. IF it does - there is a bug in the command parsing module
}

bool initiateChessGame(CHESS_MATCH **match){
    int status = 0;
    while (status == 0){
        SETTING_STATE_COMMAND *cmd = parseUserCommand();
        status = evaluateSettingStateCommand(match, cmd);
        destroyStateCommand(cmd);
    }
    bool retValue = (status == 1) ? true : false;
    return retValue;
}

