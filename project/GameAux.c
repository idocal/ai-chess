//
// Created by Ido on 8/13/17.
//

#include "GameAux.h"

#define UNDO_CAPACITY 6
#define color(player) ((player == 0) ? "black" : "white")
#define opponent(player) ((char) (1 - player))

// Match settings state messages
#define INVALID_COMMAND_ERROR "Invalid command. Please try again\n"
#define SET_ONE_PLAYER_COMMAND "Game mode is set to 1 player\n"
#define SET_TWO_PLAYERS_COMMAND "Game mode is set to 2 players\n"
#define WRONG_GAME_MODE_COMMAND "Wrong game mode\n"
#define WRONG_DIFFICULTY_LEVEL_ERROR "Wrong difficulty level. the value should be between 1 to 5\n"
#define LOAD_FILE_ERROR "Eror: File doesn't exist or cannot be opened\n"
#define EXIT_MESSAGE "Exiting...\n"

// Game state messages
#define NEXT_MOVE_MESSAGE "player - enter your move:\n"
#define INVALID_POSITION_MESSAGE "Invalid position on the board\n"
#define NO_PLAYER_PIECE_LOCATION_MESSAGE "The specified position does not contain your piece\n"
#define ILLEGAL_MOVE_MESSAGE "Illegal move\n"
#define UNDO_UNAVAILABLE_MESSAGE "Undo command not avaialbe in 2 players mode\n"
#define EMPTY_HISTORY_MESSAGE "Empty history, move cannot be undone\n"
#define RESTARTING_MESSAGE "Restarting...\n"
#define CHECKMATE_MESSAGE "Checkmate! %s player wins the game\n"
#define TIE_MESSAGE "The game is tied\n"
#define CHECK_MESSAGE "Check: %s King is threatend!\n"

int evaluateSettingStateCommand(CHESS_MATCH **matchPtr, SETTING_STATE_COMMAND *cmd) {
    SETTING_STATE_COMMAND_NAME name = cmd->command_name;
    int arg = cmd->commandArgument;
    char *addressArg = cmd->addressForLoadCommand;
    CHESS_MATCH *match = *matchPtr;

    switch(name) {
        case INVALID_COMMAND : {
            printf(INVALID_COMMAND_ERROR);
            return 0;
        }

        case GAME_MODE : {
            if (arg == 1 || arg == 2) {
                match->gameMode = arg;
                (arg == 1) ? printf(SET_ONE_PLAYER_COMMAND) : printf(SET_TWO_PLAYERS_COMMAND);
            } else {
                printf(WRONG_GAME_MODE_COMMAND);
            }
            return 0;
        }

        case DIFFICULTY : {
            if (match->gameMode == 1) {
                if (arg >= 1 && arg <= 5) match->level = arg;
                else printf(WRONG_DIFFICULTY_LEVEL_ERROR);
            }
            return 0;
        }

        case USER_COLOR : {
            if (match->gameMode == 1) match->userColor = arg;
            return 0;
        }

        case LOAD : {
            CHESS_MATCH *newMatch = parseXMLGameFile(addressArg);
            if (newMatch == NULL){
                printf(LOAD_FILE_ERROR);
                return 0;
            }
            CHESS_MATCH *destroyMatch = match;
            *matchPtr = newMatch;
            destroyChessMatch(destroyMatch);
            return 1;
        }

        case DEFAULT : {
            resetMatchSettings(match);
            return 0;
        }

        case PRINT_SETTING : {
            printMatchSettings(match);
            return 0;
        }

        case QUIT : {
            printf(EXIT_MESSAGE);
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

void printUndoMessage(CHESS_GAME *game, GAME_MOVE *move) {
    char player = game->currentPlayer;
    char sourceX = (char) move->sourceRowIndex;
    char sourceY = (char) move->sourceColIndex;
    char destX = (char) move->destRowIndex;
    char destY = (char) move->destColIndex;
    sourceX += '1'; destX += '1';
    sourceY += 'A'; destY += 'A';

    printf("Undo move for player %s : <%c,%c> -> <%c,%c>\n", color(player), sourceX, sourceY, destX, destY);
}

void handleUndoMove(CHESS_GAME *game, MOVES_STACK *stack) {
    GAME_MOVE *prevMove = pop(stack);
    revertMove(game, prevMove);
    printUndoMessage(game, prevMove);
    destroyGameMove(prevMove);
}

int evaluateGameStateCommand(CHESS_MATCH *match, GAME_STATE_COMMAND *cmd, MOVES_STACK *stack) {
    CHESS_GAME *game = match->game;
    GAME_STATE_COMMAND_NAME name = cmd->command_name;
    GAME_MOVE *move = cmd->move;
    int mode = match->gameMode;
    char *filename = cmd->filename;
    int x = cmd->x;
    int y = cmd->y;
    char player = game->currentPlayer;

    int destX = move->destRowIndex;
    int destY = move->destColIndex;
    int sourceX = move->sourceRowIndex;
    int sourceY = move->sourceColIndex;

    switch (name) {
        case INVALID_GAME_COMMAND : {
            printf(INVALID_COMMAND_ERROR);
            return 0;
        }

        case MOVE : {
            if (isOutOfBounds(destX, destY)) printf(INVALID_POSITION_MESSAGE);
            else if (!isSlotOccupied(game, sourceX, sourceY, player)) printf(NO_PLAYER_PIECE_LOCATION_MESSAGE);
            else if (!isMoveLegal(game, move)) printf(ILLEGAL_MOVE_MESSAGE);
            else {
                performMove(game, move);
                push(stack, move);
            }
            return 0;
        }

        case GET_MOVES : {
            //TODO: define how to represent possible moves on the screen
            MATRIX *possibleMoves = getPossibleMoves(game, x, y);
            return 0;
        }

        case SAVE : {
            writeMatchObjectToXmlFile(match, filename);
            return 0;
        }

        case UNDO : {
            if (mode == 2) printf(UNDO_UNAVAILABLE_MESSAGE);
            else if (peek(stack) == NULL) printf(EMPTY_HISTORY_MESSAGE);
            else {
                // twice for computer's turn as well
                handleUndoMove(game, stack);
                game->currentPlayer = opponent(player);
                handleUndoMove(game, stack);
                game->currentPlayer = opponent(player);
            }
        }

        case RESET : {
            printf(RESTARTING_MESSAGE);
            return 1;
        }

        case QUIT_GAME : {
            printf(EXIT_MESSAGE);
            return 2;
        }

        default : return -1; // this should not happen. IF it does - there is a bug in the command parsing module
    }
}

bool initiateChessGame(CHESS_MATCH *match) {
    CHESS_GAME *game = match->game;
    GAME_STATUS state = game->status;
    char player = game->currentPlayer;
    int mode = match->gameMode;
    int status = 0;
    bool firstTurn = true;

    MOVES_STACK *stack = createEmptyStack(UNDO_CAPACITY);

    // Game state loop
    while (status == 0) {
        if (!firstTurn) game->currentPlayer = opponent(player); // switch turns
        firstTurn = false;
        updateGameState(game); // detect check or checkmate or tie
        
        if (state == MATE) printf(CHECKMATE_MESSAGE, color(opponent(player)));
        else if (state == TIE) printf(TIE_MESSAGE);
        else {
            printChessGameBoard(game);
            if (state == CHECK) printf(CHECK_MESSAGE, color(player));
            printf("%s %s", color(game->currentPlayer), NEXT_MOVE_MESSAGE);
            GAME_STATE_COMMAND *cmd = parseUserGameCommand();
            status = evaluateGameStateCommand(match, cmd, stack);
        }
    }

    // Game is terminated after loop
    destroyChessMatch(match);
    destroyStack(stack);

    bool retValue = (status == 1) ? true : false;
    return retValue;
}