//
// Created by Ido on 9/10/17.
//

#include "GameWindow.h"

void setPiecesOnBoard(GENERIC_WINDOW *window);

int drawGameWindow(GENERIC_WINDOW *genericWindow) {
//    unsigned numWidgets = 16 + 16 + 1 + 6; // pieces + board + buttons
    unsigned numWidgets = 1;
    genericWindow->numWidgets = numWidgets;
    genericWindow->type = GAME_WINDOW;
    genericWindow->handleWindowEvent = (void *) gameWindowEventHandler;

    // Create SDL Window
    SDL_Window *window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if (window == NULL) {
        SDL_Quit();
        return -1;
    }
    genericWindow->window = window;

    // Create renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        genericWindow->window = NULL;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    genericWindow->renderer = renderer;

    WIDGET **widgets = (WIDGET **) calloc(numWidgets, sizeof(WIDGET *));
    if (widgets == NULL) {
        SDL_DestroyRenderer(renderer);
        genericWindow->window = NULL;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    genericWindow->widgets = widgets;

    widgets[0] = createWidget(createBoard, renderer);
    if (widgets[0] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(window);
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