//
// Created by Ido on 8/13/17.
//

#include "GameAux.h"


// Match settings state messages
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

// Game state messages
#define color(x) ((x == 0) ? "black" : "white")
#define NEXT_MOVE_MESSAGE "player - enter your move:\n"
#define INVALID_POSITION_MESSAGE "Invalid position on the board\n"
#define NO_PLAYER_PIECE_LOCATION_MESSAGE "The specified position does not contain your piece\n"
#define ILLEGAL_MOVE "Illegal move\n"

int evaluateSettingStateCommand(CHESS_MATCH **matchPtr, SETTING_STATE_COMMAND *cmd) {
    SETTING_STATE_COMMAND_NAME name = cmd->command_name;
    int arg = cmd->commandArgument;
    char *addressArg = cmd->addressForLoadCommand;
    CHESS_MATCH *match = *matchPtr;

    switch(name) {
        case INVALID_COMMAND : {
            printf(PRINT_INVALID_COMMAND_ERROR);
            return 0;
        }

        case GAME_MODE : {
            if (arg == 1 || arg == 2) {
                match->gameMode = arg;
                (arg == 1) ? printf(PRINT_SET_ONE_PLAYER_COMMAND) : printf(PRINT_SET_TWO_PLAYERS_COMMAND);
            } else {
                printf(PRINT_WRONG_GAME_MODE_COMMAND);
            }
            return 0;
        }

        case DIFFICULTY : {
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

        case USER_COLOR : {
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

        case LOAD : {
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

        case DEFAULT : {
            printf(PRINT_GAME_SETTING_DEFAULT);
            resetMatchSettings(match);
            return 0;
        }

        case PRINT_SETTING : {
            printMatchSettings(match);
            return 0;
        }

        case QUIT : {
            printf(PRINT_EXIT_MESSAGE);
            return 2;
        }

        case START : {
            initGameBoard(match->game);
            return 1;
        }

        default : return -1; // this should not happen. IF it does - there is a bug in the command parsing module
    }
}

bool initiateChessMatch(CHESS_MATCH **match){
    int status = 0;
    while (status == 0){
        SETTING_STATE_COMMAND *cmd = parseUserSettingCommand();
        status = evaluateSettingStateCommand(match, cmd);
        destroyStateCommand(cmd);
    }
    bool retValue = (status == 1) ? true : false;
    return retValue;
}

int evaluateGameStateCommand(CHESS_GAME *game, GAME_STATE_COMMAND *cmd, int mode) {
    GAME_STATE_COMMAND_NAME name = cmd->command_name;
    GAME_MOVE *move = cmd->move;
    char *filename = cmd->filename;
    int x = cmd->x;
    int y = cmd->y;
    char player = game->currentPlayer;


    switch (name) {
//        MOVE,
//        GET_MOVES,
//        SAVE,
//        UNDO,
//        RESET,
//        INVALID_GAME_COMMAND
        case MOVE : {
            int destX = move->destRowIndex;
            int destY = move->destColIndex;
            int sourceX = move->sourceRowIndex;
            int sourceY = move->sourceColIndex;

            if (isOutOfBounds(destX, destY)) printf(INVALID_POSITION_MESSAGE);
            else if (!isSlotOccupied(game, sourceX, sourceY, player)) printf(NO_PLAYER_PIECE_LOCATION_MESSAGE);
            else if (!isMoveLegal(game, move)) printf(ILLEGAL_MOVE);
            else performMove(game, move);
            return 0;
        }

        default : return -1; // this should not happen. IF it does - there is a bug in the command parsing module
    }
}

void initiateChessGame(CHESS_MATCH *match) {
    CHESS_GAME *game = match->game;
    int mode = match->gameMode;
    int status = 0;

    while (status == 0) {
        printChessGameBoard(game);
        printf("%s %s", color(game->currentPlayer), NEXT_MOVE_MESSAGE);
        SETTING_STATE_COMMAND *cmd = parseUserSettingCommand();
        status = evaluateGameStateCommand(game, cmd, mode);
    }
}