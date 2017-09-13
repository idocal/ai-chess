//
// Created by Ido on 9/10/17.
//

#include "GameWindow.h"


int drawGameWindow(GENERIC_WINDOW *genericWindow, SDL_Window *sdlWindow, SDL_Renderer *renderer, CHESS_MATCH *match) {
    unsigned numWidgets = 16 + 16 + 1 + 6; // pieces + board + buttons
    int numWidgetsCreated = 0;
    genericWindow->numWidgets = numWidgets;
    genericWindow->type = GAME_WINDOW;
    genericWindow->handleWindowEvent = (void *) gameWindowEventHandler;

    // Assign the application window and renderer
    genericWindow->window = sdlWindow;
    genericWindow->renderer = renderer;


    WIDGET **widgets = (WIDGET **) calloc(numWidgets, sizeof(WIDGET *));
    if (widgets == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
    genericWindow->widgets = widgets;

    widgets[0] = createWidget(createBoard, renderer);
    if (widgets[0] == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
    numWidgetsCreated++;

    numWidgetsCreated += setPiecesOnBoard(genericWindow); // function returns number of pieces created
    if (numWidgetsCreated < 33) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // if setPieces failed (did not create 32 pieces)

    widgets[33] = createWidget(createRestartButton, renderer);
    if (widgets[33] == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
    numWidgetsCreated++;

    widgets[34] = createWidget(createSaveButton, renderer);
    if (widgets[34] == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
    numWidgetsCreated++;

    widgets[35] = createWidget(createLoadButtonGame, renderer);
    if (widgets[35] == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
    numWidgetsCreated++;

    widgets[36] = createWidget(createUndoButton, renderer);
    if (widgets[36] == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
    numWidgetsCreated++;
    widgets[36]->isEnable = false; // By default undo is disabled

    widgets[37] = createWidget(createMenuButton, renderer);
    if (widgets[37] == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
    numWidgetsCreated++;

    widgets[38] = createWidget(createExitButtonGame, renderer);
    if (widgets[38] == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
    numWidgetsCreated++;
    
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

EVENT_RESPONSE *gameWindowEventHandler(GENERIC_WINDOW *window, SDL_Event *event, CHESS_MATCH *match, MOVES_STACK *stack) {
    WINDOW_TYPE nextWindow = GAME_WINDOW;
    int widgetIndex = getClickedWidget(window, event);
    WIDGET *widget = window->widgets[widgetIndex];
    SDL_Renderer *renderer = window->renderer;
    int mode = match->gameMode;
    EVENT_RESPONSE *response = createEventResponse(nextWindow, SAME_WINDOW);

    if (widgetIndex >= 1 && widgetIndex <= 32) { // Piece handle
        handlePieceEvent(window, event, match, stack, widgetIndex);
    }

    if (widgetIndex == 33) { // The button clicked is Restart
        CHESS_GAME *newGame = createEmptyGame();
        initGameBoard(newGame);
        destroyChessGame(match->game);
        match->game = newGame;
        response->windowType = GAME_WINDOW;
        response->status = NEW_WINDOW;
    }

    if (widgetIndex == 34) { // The button clicked is Save
        writeMatchObjectToXmlFile(match, SAVE_FILEPATH);
        //TODO: save this game to game slot 1
    }

    if (widgetIndex == 35) { // The button clicked is Load
        response->windowType = LOAD_WINDOW;
        response->status = NEW_WINDOW;
    }

    if (widgetIndex == 36) { // The button clicked is Undo
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

    if (widgetIndex == 37) { // The button clicked is Main Menu
        CHESS_GAME *newGame = createEmptyGame();
        initGameBoard(newGame);
        destroyChessGame(match->game);
        match->game = newGame;
        resetMatchSettings(match);
        response->windowType = WELCOME_WINDOW;
        response->status = NEW_WINDOW;
    }

    if (widgetIndex == 38) { // The button clicked is Exit
        response->status = EXIT_WINDOW;
    }

    return response;
}

void handlePieceEvent(GENERIC_WINDOW *window, SDL_Event *event, CHESS_MATCH *match, MOVES_STACK *stack, int widgetIndex) {
    WIDGET *widget = window->widgets[widgetIndex];
    WIDGET *undoButton = window->widgets[36];

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
                    swapTurns(match, stack, window);
                    if (!undoButton->isEnable && match->gameMode == 1) { // Enable undo button
                        toggleButtonAbility(undoButton, window->renderer);
                        reRenderWindow(window);
                    }
                }

                break;
            }
        }
    }
}