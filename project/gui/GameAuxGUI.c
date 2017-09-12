//
// Created by Ido on 9/11/17.
//

#include "GameAuxGUI.h"

int moveToPosition(CHESS_GAME *game, GENERIC_WINDOW *window, WIDGET *widget, int x, int y, MOVES_STACK *stack) {
    char player = game->currentPlayer;
    int sourceRow = widget->position->row;
    int sourceCol = widget->position->col;

    BOARD_POSITION *newPosition = calculateBoardPosition(x, y);
    GAME_MOVE *move = createGameMove(game, sourceRow, sourceCol, newPosition->row, newPosition->col); // Create move from original to <x,y>

    // Perform move if it's a legal one
    if (move == NULL) {
        widget->rect.x = screenPositionX(widget->position->col);
        widget->rect.y = screenPositionY(widget->position->row);
        reRenderWindow(window);
        return -1;
    }
    else if (!isSlotOccupied(game, move->sourceRowIndex, move->sourceColIndex, player)) {
        widget->rect.x = screenPositionX(widget->position->col);
        widget->rect.y = screenPositionY(widget->position->row);
        reRenderWindow(window);
        return -1;
    }
    else if (!isMoveLegal(game, move)) {
        widget->rect.x = screenPositionX(widget->position->col);
        widget->rect.y = screenPositionY(widget->position->row);
        reRenderWindow(window);
        return -1;
    }
    else {
        if (isConquer(move)) { // If conquering, remove opponent's piece
            WIDGET *conqueredPiece = findWidget(window, screenPositionX(newPosition->col), screenPositionY(newPosition->row));
            hidePiece((conqueredPiece));
        }

        // Update widget with new position
        widget->position->row = newPosition->row;
        widget->position->col = newPosition->col;


        // Move widget to screen position
        widget->rect.x = screenPositionX(newPosition->col);
        widget->rect.y = screenPositionY(newPosition->row);
        reRenderWindow(window);

        // Perform move on game representation
        performMove(game, move);
        push(stack, move);
    }

    free(newPosition);
    return 1;
}

void swapTurns(CHESS_MATCH *match, MOVES_STACK *stack, GENERIC_WINDOW *window) {
    CHESS_GAME *game = match->game;
    int mode = match->gameMode;
    char player = game->currentPlayer;
    updateGameState(game); // This will change game->state to the correct one

    if (game->status == MATE) handleWin(opponent(player));
    else if (game->status == TIE) handleTie();
    else {
        if (mode == 2) switchPlayers(game); // If two players mode, change current player.
        else { // one player, perform AI move
            if (handleAIMove(match, stack, window) == -1) return; // An error occurred while trying to perform AI move
        }
    }

    if (game->pruningThreshold > 0) game->pruningThreshold -= 0.01; // Tweak for expert level pruning
}

int handleAIMove(CHESS_MATCH *match, MOVES_STACK *stack, GENERIC_WINDOW *window) {
    CHESS_GAME *game = match->game;
    switchPlayers(game); // switch to opponent for computer move
    int maxDepth;
    GAME_MOVE *AIMove = NULL;

    if (match->level == 5) {
        maxDepth = 4;
        AIMove = AINextMove(game, &(maxDepth), true);
    } else {
        maxDepth = match->level;
        AIMove = AINextMove(game, &(maxDepth), false);
    }
    if (AIMove == NULL) return -1;

    int widgetX = screenPositionX(AIMove->sourceColIndex);
    int widgetY = screenPositionY(AIMove->sourceRowIndex);
    WIDGET *widget = findWidget(window, widgetX, widgetY);

    int x = screenPositionX(AIMove->destColIndex);
    int y = screenPositionY(AIMove->destRowIndex);

    moveToPosition(game, window, widget, x, y, stack);
    switchPlayers(game); // switch back to player

    return 1;
}

WIDGET *findWidget(GENERIC_WINDOW *window, int x, int y) {
    for (int i = 0; i < window->numWidgets; i++) {
        WIDGET *widget = window->widgets[i];
        if (widget->rect.x == x && widget->rect.y == y) return widget;
    }
    return NULL; // this should never happen unless location <x,y> is invalid
}

void handleWin(char playerWon) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game over!", playerColor(playerWon), NULL);
}

void handleTie() {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Game over!", "It\'s a tie", NULL);
}

void hidePiece(WIDGET *widget) {
    widget->rect.x = -80; // Out of the screen
    widget->rect.y = -80; // Out of the screen
    widget->position->row = -1;
    widget->position->col = -1;
    widget->isEnable = false;
    widget->isClickable = false;
}