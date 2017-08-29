//
// Created by Ido on 8/13/17.
//

#include "GameAux.h"

int applyGameState(CHESS_GAME *);
int AIMove(CHESS_MATCH *, MOVES_STACK *);

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

        default : return -1; // this should not happen. If it does - there is a bug in the command parsing module
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
    int sourceX = move->sourceRowIndex;
    int sourceY = move->sourceColIndex;
    int destX = move->destRowIndex;
    int destY = move->destColIndex;
    sourceX += '1'; destX += '1';
    sourceY += 'A'; destY += 'A';

    printf("Undo move for player %s : <%c,%c> -> <%c,%c>\n", color(player), destX, destY, sourceX, sourceY);
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

    if (move != NULL) { // update move original symbols for revert
        move->sourceOriginalSymbol = matGet(game->gameBoard, move->sourceRowIndex, move->sourceColIndex);
        move->destOriginalSymbol = matGet(game->gameBoard, move->destRowIndex, move->destColIndex);
    }

    switch (name) {
        case INVALID_GAME_COMMAND : {
            printf(INVALID_COMMAND_ERROR);
            return 3;
        }

        case MOVE : {
            if (move == NULL) {
                printf(INVALID_POSITION_MESSAGE);
                return 3; // should not print board
            }
            else if (!isSlotOccupied(game, move->sourceRowIndex, move->sourceColIndex, player)) {
                printf(NO_PLAYER_PIECE_LOCATION_MESSAGE);
                return 3; // should not print board
            }
            else if (!isMoveLegal(game, move)) {
                printf(ILLEGAL_MOVE_MESSAGE);
                return 3; // should not print board
            }
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
            else if (stack->currentSize == 0) printf(EMPTY_HISTORY_MESSAGE);
            else {
                // twice for computer's turn as well
                switchPlayers(game);
                handleUndoMove(game, stack);
                switchPlayers(game);
                handleUndoMove(game, stack);
                printChessGameBoard(game);
            }
            return 3;
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
    int mode = match->gameMode;
    bool firstTurn = true;
    int status = 0;

    MOVES_STACK *stack = createEmptyStack(UNDO_CAPACITY);

    // Game state loop
    while (status == 0 || status == 3) {
        bool shouldPrintMessage = (status == 3) ? false : true;

        if (shouldPrintMessage && mode == 2) { // if message is printed, current player should not switch (only 2 players mode)
            if (!firstTurn) switchPlayers(game); // switch turns
        }

        char player = game->currentPlayer;
        firstTurn = false;

        status = applyGameState(game);

        if (shouldPrintMessage) {
            printChessGameBoard(game);
            if (game->status == CHECK) {
                if (mode == 1) printf(CHECK_AI_MESSAGE);
                if (mode == 2) printf(CHECK_MESSAGE, color(player));
            }
            printf("%s %s", color(game->currentPlayer), NEXT_MOVE_MESSAGE);
        }

        GAME_STATE_COMMAND *cmd = parseUserGameCommand();
        status = evaluateGameStateCommand(match, cmd, stack);
        destroyGameCommand(cmd);

        if (status == 0 && mode == 1)  {
            status = AIMove(match, stack); // If command passed correctly, perform AI move
            if (status == -1) { // AI Move failed (probably memory allocation problem)
                status = 2;
                printf(FATAL_ERROR_MESSAGE);
            }
        }
    }

    // Game is terminated after loop
    destroyChessMatch(match);
    destroyStack(stack);

    bool retValue = (status == 1) ? true : false; // quitting the loop is only status 1 or 2.
    return retValue;
}

int applyGameState(CHESS_GAME *game) {
    updateGameState(game); // detect check or checkmate or tie
    GAME_STATUS state = game->status;
    char player = game->currentPlayer;

    if (state == MATE) {
        printf(CHECKMATE_MESSAGE, color(opponent(player)));
        return 2;
    }

    else if (state == TIE) {
        printf(TIE_MESSAGE);
        return 2;
    }

    return 0;
}

void handleAIMoveMessage(GAME_MOVE *AIMove) {
    int x = AIMove->sourceRowIndex;
    int y = AIMove->sourceColIndex;
    int i = AIMove->destRowIndex;
    int j = AIMove->destColIndex;
    char movedPiece[PIECE_NAME_SIZE];

    int X = x + '1';
    int Y = y + 'A';
    int I = i + '1';
    int J = j + 'A';

    strcpy(movedPiece, pieceName(AIMove->sourceOriginalSymbol));
    printf(COMPUTER_MOVE_MESSAGE, movedPiece, X, Y, I, J);
}

int AIMove(CHESS_MATCH *match, MOVES_STACK *stack) {
    CHESS_GAME *game = match->game;
    switchPlayers(game); // switch to opponent for computer move
    int status = applyGameState(game);
    if (status == 0) { // game is not over
        GAME_MOVE *AIMove = AINextMove(game, &(match->level));
        if (AIMove == NULL) return -1;
        performMove(game, AIMove);
        push(stack, AIMove);
        switchPlayers(game); // switch back to player

        handleAIMoveMessage(AIMove);

    }

    return status;
}