//
// Created by Ido on 9/10/17.
//

#include "GameWindow.h"

void setPiecesOnBoard(GENERIC_WINDOW *window);

int drawGameWindow(GENERIC_WINDOW *genericWindow, SDL_Window *sdlWindow, SDL_Renderer *renderer) {
    SDL_SetWindowSize(sdlWindow, WINDOW_WIDTH, WINDOW_HEIGHT);
//    unsigned numWidgets = 16 + 16 + 1 + 6; // pieces + board + buttons
    unsigned numWidgets = 1;
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


    reRenderWindow(genericWindow);

    return 1;
}

int createBoard(WIDGET *widget, SDL_Renderer *renderer) {
    int x = WINDOW_WIDTH - BUTTON_MARGIN - 640;
    return createBackground(x, PAGE_MARGIN, 640, 640, "./img/board.bmp", renderer, widget);
}

EVENT_RESPONSE *gameWindowEventHandler(GENERIC_WINDOW *window, SDL_Event *event, CHESS_MATCH *match) {
    GENERIC_WINDOW *nextWindow = window;
    int widgetIndex = getClickedWidget(window, event);
    WIDGET *widget = window->widgets[widgetIndex];
    SDL_Renderer *renderer = window->renderer;
    EVENT_RESPONSE *response = createEventResponse(window, SAME_WINDOW);

    if (widgetIndex >= 1 || widgetIndex <= 32) { // Piece handle

    }

    return response;
}

void setPiecesOnBoard(GENERIC_WINDOW *window) {
    WIDGET **widgets = window->widgets;


}