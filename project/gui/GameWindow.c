//
// Created by Ido on 9/10/17.
//

#include "GameWindow.h"


int drawGameWindow(GENERIC_WINDOW *genericWindow, SDL_Window *sdlWindow, SDL_Renderer *renderer, CHESS_MATCH *match) {
    genericWindow->numWidgets = 0;
    genericWindow->type = GAME_WINDOW;
    genericWindow->handleWindowEvent = gameWindowEventHandler;

    // Assign the application window and renderer
    genericWindow->window = sdlWindow;
    genericWindow->renderer = renderer;


    WIDGET **widgets = (WIDGET **) calloc(39 + 32, sizeof(WIDGET *)); // 39 is 16 + 16 + 6 + 1 (pieces + buttons + board) 32 is number of max overlays
    if (widgets == NULL) return destroyWindowOnFailure(genericWindow, genericWindow->numWidgets); // On failure
    genericWindow->widgets = widgets;

    widgets[0] = createWidget(createBoard, renderer);
    if (widgets[0] == NULL) return destroyWindowOnFailure(genericWindow, genericWindow->numWidgets); // On failure
    genericWindow->numWidgets++;

    // Set pieces on board according to match game board
    genericWindow->numWidgets += setPiecesOnBoard(genericWindow, match); // function returns number of pieces created

    widgets[genericWindow->numWidgets] = createWidget(createRestartButton, renderer);
    if (widgets[genericWindow->numWidgets] == NULL) return destroyWindowOnFailure(genericWindow, genericWindow->numWidgets); // On failure
    genericWindow->numWidgets++;

    widgets[genericWindow->numWidgets] = createWidget(createSaveButton, renderer);
    if (widgets[genericWindow->numWidgets] == NULL) return destroyWindowOnFailure(genericWindow, genericWindow->numWidgets); // On failure
    genericWindow->numWidgets++;

    widgets[genericWindow->numWidgets] = createWidget(createLoadButtonGame, renderer);
    if (widgets[genericWindow->numWidgets] == NULL) return destroyWindowOnFailure(genericWindow, genericWindow->numWidgets); // On failure
    genericWindow->numWidgets++;

    widgets[genericWindow->numWidgets] = createWidget(createUndoButton, renderer);
    if (widgets[genericWindow->numWidgets] == NULL) return destroyWindowOnFailure(genericWindow, genericWindow->numWidgets); // On failure
    (widgets[genericWindow->numWidgets])->isEnable = false; // By default undo is disabled
    genericWindow->numWidgets++;

    widgets[genericWindow->numWidgets] = createWidget(createMenuButton, renderer);
    if (widgets[genericWindow->numWidgets] == NULL) return destroyWindowOnFailure(genericWindow, genericWindow->numWidgets); // On failure
    genericWindow->numWidgets++;

    widgets[genericWindow->numWidgets] = createWidget(createExitButtonGame, renderer);
    if (widgets[genericWindow->numWidgets] == NULL) return destroyWindowOnFailure(genericWindow, genericWindow->numWidgets); // On failure
    genericWindow->numWidgets++;

    reRenderWindow(genericWindow);

    if (match->gameMode == 1 && match->userColor == 0) { // Single player mode and user color is black
        handleAIFirstMove(match, genericWindow);
        reRenderWindow(genericWindow);
    }

    return 1;
}

int createBoard(WIDGET *widget, SDL_Renderer *renderer) {
    int x = WINDOW_WIDTH - BUTTON_MARGIN - BOARD_WIDTH;
    return createBackground(x, PAGE_MARGIN, BOARD_WIDTH, BOARD_HEIGHT, "./img/board.bmp", renderer, widget);
}

int createRestartButton(WIDGET *widget, SDL_Renderer *renderer) {
    return createButton(BUTTON_MARGIN, PAGE_MARGIN, "./img/restart.bmp", renderer, widget, false);
}

int createSaveButton(WIDGET *widget, SDL_Renderer *renderer) {
    return createButton(BUTTON_MARGIN, PAGE_MARGIN + BUTTON_MARGIN/2 + BUTTON_HEIGHT, "./img/save.bmp", renderer, widget, false);
}

int createLoadButtonGame(WIDGET *widget, SDL_Renderer *renderer) {
    return createButton(BUTTON_MARGIN, PAGE_MARGIN + 2 * BUTTON_MARGIN/2 + 2 * BUTTON_HEIGHT, "./img/load.bmp", renderer, widget, false);
}

int createUndoButton(WIDGET *widget, SDL_Renderer *renderer) {
    return createButton(BUTTON_MARGIN, PAGE_MARGIN + 3 * BUTTON_MARGIN/2 + 3 * BUTTON_HEIGHT, "./img/undo_disabled.bmp", renderer, widget, false);
}

int createMenuButton(WIDGET *widget, SDL_Renderer *renderer) {
    return createButton(BUTTON_MARGIN, PAGE_MARGIN + 4 * BUTTON_MARGIN/2 + 4 * BUTTON_HEIGHT, "./img/main_menu.bmp", renderer, widget, false);
}

int createExitButtonGame(WIDGET *widget, SDL_Renderer *renderer) {
    return createButton(BUTTON_MARGIN, PAGE_MARGIN + 5 * BUTTON_MARGIN/2 + 5 * BUTTON_HEIGHT, "./img/exit.bmp", renderer, widget, false);
}

void removeOverlays(GENERIC_WINDOW *window) {
    for (int i = 0; i < window->overlays; i++) {
        int numWidgets = window->numWidgets + i;
        destroyWidget(window->widgets[numWidgets]);
    }
    window->overlays = 0;
    reRenderWindow(window);
}

EVENT_RESPONSE *gameWindowEventHandler(GENERIC_WINDOW *window, SDL_Event *event, CHESS_MATCH *match, MOVES_STACK *stack) {
    WINDOW_TYPE nextWindow = GAME_WINDOW;
    int widgetIndex = getClickedWidget(window, event);
    WIDGET *widget = window->widgets[widgetIndex];
    SDL_Renderer *renderer = window->renderer;
    int mode = match->gameMode;
    EVENT_RESPONSE *response = createEventResponse(nextWindow, SAME_WINDOW);
    int numWidgets = window->numWidgets;
    char player = match->game->currentPlayer;

    if (event->button.button == SDL_BUTTON_LEFT) {
        removeOverlays(window); // on left click remove any overlays remaining

        if (widgetIndex >= 1 && widgetIndex <= numWidgets - 7) { // Piece handle
            if (!handlePieceEvent(window, event, match, stack, widgetIndex)) response->status = EXIT_WINDOW;
        }

        if (widgetIndex == numWidgets - 6) { // The button clicked is Restart
            CHESS_GAME *newGame = createEmptyGame();
            initGameBoard(newGame);
            destroyChessGame(match->game);
            match->game = newGame;
            response->windowType = GAME_WINDOW;
            response->status = NEW_WINDOW;
        }

        if (widgetIndex == numWidgets - 5) { // The button clicked is Save
            int numSavedFiles = getNumSavedFilesInGameDir();
            if (numSavedFiles == -1){  // memory error occurred prompt a messages that the games wasn't saved
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, SAVE_ERROR_TITLE, SAVE_GAME_ERROR_MESSAGE, NULL);
                return response;
            }
            int i = (numSavedFiles == MAXIMUM_NUMBER_OF_SAVED_GAMES_SLOTS) ? numSavedFiles -1 : numSavedFiles;
            for (; i > 0; --i) {
                int swapRes = swapBetweenAdjacentSavedGames(i, i + 1);
                if (swapRes == -1) { // an error occurred. show message and return to game
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, SAVE_ERROR_TITLE, SAVE_GAME_ERROR_MESSAGE, NULL);
                    return response;
                }
            }
            writeMatchObjectToXmlFile(match, SAVE_FILE_PATH);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, SAVE_SUCCESSFUL_TITLE, SAVE_GAME_BODY_MESSAGE, NULL);
        }

        if (widgetIndex == numWidgets - 4) { // The button clicked is Load
            response->windowType = LOAD_WINDOW;
            response->status = NEW_WINDOW;
        }

        if (widgetIndex == numWidgets - 3) { // The button clicked is Undo
            if (mode == 2) return response;
            else if (stack->currentSize == 0) return response;
            else {
                switchPlayers(match->game);
                handleUndo(match->game, stack, window);
                switchPlayers(match->game);
                handleUndo(match->game, stack, window);
                if (stack->currentSize == 0) { // Turn off undo button if reached empty stack
                    toggleButtonAbility(window->widgets[widgetIndex], renderer);
                    reRenderWindow(window);
                }

            }
        }

        if (widgetIndex == numWidgets - 2) { // The button clicked is Main Menu
            CHESS_GAME *newGame = createEmptyGame();
            initGameBoard(newGame);
            destroyChessGame(match->game);
            match->game = newGame;
            resetMatchSettings(match);
            response->windowType = WELCOME_WINDOW;
            response->status = NEW_WINDOW;
        }

        if (widgetIndex == numWidgets - 1) { // The button clicked is Exit
            response->status = EXIT_WINDOW;
        }
    }

    if (event->button.button == SDL_BUTTON_RIGHT) {
        removeOverlays(window); // on right click remove any overlays remaining
        if (widgetIndex >= 1 && widgetIndex <= numWidgets - 7) { // Piece handle
            char piece = widget->piece;
            if (pieceOwner(piece, player)) {
                int x = screenPositionX(widget->position->col);
                int y = screenPositionY(widget->position->row);
                handleGetMoves(match->game, widget->position->row, widget->position->col, window, match->level);
            }
        }
    }
    return response;
}

bool handlePieceEvent(GENERIC_WINDOW *window, SDL_Event *event, CHESS_MATCH *match, MOVES_STACK *stack, int widgetIndex) {
    WIDGET *widget = window->widgets[widgetIndex];
    WIDGET *undoButton = window->widgets[window->numWidgets - 3]; // Undo is 3rd from last button

    if (widget->position != NULL) {
        int initialRow = widget->position->row;
        int initialCol = widget->position->col;
        SDL_Event dropEvent;

        int leftBound = initialX;
        int rightBound = initialX + BOARD_WIDTH;
        int upperBound = initialBlackY;
        int lowerBound = initialBlackY + BOARD_HEIGHT;

        while (true) { // Wait till mouse is up
            SDL_WaitEvent(&dropEvent); // Catch motion event

            // When going out of bounds, return piece to original location
            if (dropEvent.button.x < leftBound || dropEvent.button.x > rightBound || dropEvent.button.y < upperBound|| dropEvent.button.y > lowerBound) {
                widget->rect.x = screenPositionX(initialCol);
                widget->rect.y = screenPositionY(initialRow);
                reRenderWindow(window);
                break;
            }

            // Update widget location while dragging
            widget->rect.x = dropEvent.button.x - PIECE_SIZE / 2; // because image is not centered
            widget->rect.y = dropEvent.button.y - PIECE_SIZE / 2; // because image is not centered
            reRenderWindow(window);

            if (dropEvent.type == SDL_MOUSEBUTTONUP) { // mouse is up - drop widget
                int successMove = moveToPosition(match->game, window, widget, dropEvent.button.x, dropEvent.button.y, stack); // move piece to desired position
                if (successMove == 1) {
                    if (!swapTurns(match, stack, window)) return false; // if swapTurns returned false then game is over
                    if (!undoButton->isEnable && match->gameMode == 1) { // Enable undo button
                        toggleButtonAbility(undoButton, window->renderer);
                        reRenderWindow(window);
                    }
                }

                break;
            }
        }
    }

    return true;
}

int swapBetweenAdjacentSavedGames(int loadFromIndex, int loadToIndex){
    char filePathLoad[100];
    generateAddressToChosenGame(filePathLoad, loadFromIndex);
    CHESS_MATCH *loadedMatch = parseXMLGameFile(filePathLoad);
    if (loadedMatch == NULL){
        return -1; // memory error occurred
    }
    char filePathSave[100];
    generateAddressToChosenGame(filePathSave, loadToIndex);
    writeMatchObjectToXmlFile(loadedMatch, filePathSave);
    destroyChessMatch(loadedMatch);
    return 0;
}

void handleGetMoves(CHESS_GAME *game, int row, int col, GENERIC_WINDOW *window, int difficulty) {
    if (difficulty > 2) return; // This feature is only supported in Noob and Easy difficulties
    reRenderWindow(window);
    MATRIX *possibleMoves = getPossibleMoves(game, row, col);
    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nCols; ++j) {
            if (matGet(possibleMoves, i, j) == 1) { // if move is a possible one

                char destPiece = matGet(game->gameBoard, i, j);
                bool capture = (destPiece != '_') ? true : false; // since cell can not be player's
                CHESS_GAME *cpyGame = copyChessGame(game);
                GAME_MOVE *move = createGameMove(game, row, col, i, j); // move <x,y> -> <i,j>
                performMove(cpyGame, move);
                bool threat = isThreatened(cpyGame, i, j);
                destroyChessGame(cpyGame);
                destroyGameMove(move);

                int x = screenPositionX(j);
                int y = screenPositionY(i);

                WIDGET *moveCell;

                if (capture && threat){
                    moveCell = createMoveCell(x, y, window->renderer, MOVE_CAPTURE_THREAT);
                } else if (capture){
                    moveCell = createMoveCell(x, y, window->renderer, MOVE_CAPTURE);
                } else if (threat){
                    moveCell = createMoveCell(x, y, window->renderer, MOVE_THREAT);
                } else{
                    moveCell = createMoveCell(x, y, window->renderer, MOVE_REGULAR);
                }

                int numWidgets = window->numWidgets + window->overlays;
                if (moveCell == NULL) destroyWindowOnFailure(window, numWidgets);

                window->widgets[numWidgets] = moveCell;
                window->overlays++;
            }
        }
    }

    reRenderWindow(window);
    matDestroy(possibleMoves);
}