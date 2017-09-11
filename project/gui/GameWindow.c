//
// Created by Ido on 9/10/17.
//

#include "GameWindow.h"


int drawGameWindow(GENERIC_WINDOW *genericWindow, SDL_Window *sdlWindow, SDL_Renderer *renderer) {
    SDL_SetWindowSize(sdlWindow, WINDOW_WIDTH, WINDOW_HEIGHT);
    unsigned numWidgets = 16 + 16 + 1 + 6; // pieces + board + buttons
    genericWindow->numWidgets = numWidgets;
    genericWindow->type = GAME_WINDOW;
    genericWindow->handleWindowEvent = (void *) gameWindowEventHandler;

    // Assign the application window and renderer
    genericWindow->window = sdlWindow;
    genericWindow->renderer = renderer;


    WIDGET **widgets = (WIDGET **) calloc(numWidgets, sizeof(WIDGET *));
    if (widgets == NULL) {
        SDL_DestroyRenderer(renderer);
        genericWindow->window = NULL;
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
        return -1;
    }
    genericWindow->widgets = widgets;

    widgets[0] = createWidget(createBoard, renderer);
    if (widgets[0] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
        return -1;
    }

    setPiecesOnBoard(genericWindow);

    widgets[33] = createWidget(createRestartButton, renderer);
    if (widgets[33] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
        return -1;
    }

    widgets[34] = createWidget(createSaveButton, renderer);
    if (widgets[34] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
        return -1;
    }

    widgets[35] = createWidget(createLoadButtonGame, renderer);
    if (widgets[35] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
        return -1;
    }

    widgets[36] = createWidget(createUndoButton, renderer);
    if (widgets[36] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
        return -1;
    }
    widgets[36]->isEnable = false; // By default undo is disabled

    widgets[37] = createWidget(createMenuButton, renderer);
    if (widgets[37] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
        return -1;
    }

    widgets[38] = createWidget(createExitButtonGame, renderer);
    if (widgets[38] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
        return -1;
    }

    
    reRenderWindow(genericWindow);

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
    GENERIC_WINDOW *nextWindow = window;
    int widgetIndex = getClickedWidget(window, event);
    WIDGET *widget = window->widgets[widgetIndex];
    SDL_Renderer *renderer = window->renderer;
    EVENT_RESPONSE *response = createEventResponse(window, SAME_WINDOW);

    int leftBound = initialX;
    int rightBound = initialX + BOARD_WIDTH;
    int upperBound = initialBlackY;
    int lowerBound = initialBlackY + BOARD_HEIGHT;

    if (widgetIndex >= 1 && widgetIndex <= 32) { // Piece handle
        if (widget->position != NULL) {
            int initialRow = widget->position->row;
            int initialCol = widget->position->col;
            printChessGameBoard(match->game);
            printf("Position: <%d,%d>\n", initialRow, initialCol);

            SDL_Event dropEvent;
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
                widget->rect.x = dropEvent.button.x - 40; // -40 because image is not centered
                widget->rect.y = dropEvent.button.y - 40; // -40 because image is not centered
                reRenderWindow(window);

                if (dropEvent.type == SDL_MOUSEBUTTONUP) { // mouse is up - drop widget
                    moveToPosition(match->game, window, widget, dropEvent.button.x, dropEvent.button.y, stack);
                    printf("Event drop: <%d,%d>\n", dropEvent.button.x, dropEvent.button.y);
                    break;
                }
            }
            printf("END DRAG AND DROP!\n");
        }
    }

    return response;
}