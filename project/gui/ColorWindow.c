//
// Created by Ido on 9/10/17.
//

#include "ColorWindow.h"

int drawColorWindow(GENERIC_WINDOW *genericWindow) {
    int numWidgets = 5;
    genericWindow->numWidgets = numWidgets;
    genericWindow->type = SETTINGS_COLOR_WINDOW;
    genericWindow->handleWindowEvent = colorWindowEventHandler;

    // Create SDL Window
    SDL_Window *window = SDL_CreateWindow("Choose Color", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
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

    // Load widgets into widgets array
    widgets[0] = createWidget(createColorTitle, renderer);
    if (widgets[0] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    widgets[1] = createWidget(createWhiteButton, renderer);
    if (widgets[1] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    widgets[2] = createWidget(createBlackButton, renderer);
    if (widgets[2] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    widgets[3] = createWidget(createBackButton, renderer);
    if (widgets[3] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    widgets[4] = createWidget(createStartButton, renderer);
    if (widgets[4] == NULL) {
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

int createColorTitle(WIDGET *widget, SDL_Renderer *renderer) {
    return createTitle("./img/color.bmp", renderer, widget);
}

int createWhiteButton(WIDGET *widget, SDL_Renderer *renderer) {
    int x = (WINDOW_WIDTH - (2 * BUTTON_WIDTH + BUTTON_MARGIN)) / 2;
    return createButton(x, 180, "./img/white_on.bmp", renderer, widget, true);
}

int createBlackButton(WIDGET *widget, SDL_Renderer *renderer) {
    int x = (WINDOW_WIDTH - (2 * BUTTON_WIDTH + BUTTON_MARGIN)) / 2 + BUTTON_WIDTH + BUTTON_MARGIN;
    return createButton(x, 180, "./img/black.bmp", renderer, widget, false);
}

EVENT_RESPONSE *colorWindowEventHandler(GENERIC_WINDOW *window, SDL_Event *event, CHESS_MATCH *match) {
    GENERIC_WINDOW *nextWindow = window;
    int widgetIndex = getClickedWidget(window, event);
    WIDGET *widget = window->widgets[widgetIndex];
    SDL_Renderer *renderer = window->renderer;
    EVENT_RESPONSE *response = createEventResponse(window, SAME_WINDOW);

    if (widgetIndex == 1) { // White button is clicked
        if (!widget->isActive) {
            toggleButton(widget, renderer);
            toggleButton(window->widgets[2], renderer);
            reRenderWindow(window);
            match->userColor = 1;
        }
    }

    if (widgetIndex == 2) { // Black button is clicked
        if (!widget->isActive) {
            toggleButton(widget, renderer);
            toggleButton(window->widgets[1], renderer);
            reRenderWindow(window);
            match->userColor = 0;
        }
    }

    if (widgetIndex == 3) { // Back button is clicked
        response->status = BACK_WINDOW;
    }

    if (widgetIndex == 4) { // Start button is clicked
        nextWindow = createGenericWindow(drawColorWindow);
        response->window = nextWindow;
        response->status = NEW_WINDOW;
    }

    return response;
}