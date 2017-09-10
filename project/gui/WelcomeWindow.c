//
// Created by Ido on 9/9/17.
//

#include "WelcomeWindow.h"

int drawWelcomeWindow(GENERIC_WINDOW *genericWindow) {
    int numWidgets = 3;
    genericWindow->numWidgets = numWidgets;
    genericWindow->type = WELCOME_WINDOW;
    genericWindow->handleWindowEvent = welcomeWindowEventHandler;

    // Create SDL Window
    SDL_Window *window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, NARROW_WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
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
    widgets[0] = createWidget(createNewGameButton, renderer);
    if (widgets[0] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    widgets[1] = createWidget(createLoadGameButton, renderer);
    if (widgets[1] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    widgets[2] = createWidget(createExitButton, renderer);
    if (widgets[2] == NULL) {
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

int createNewGameButton(WIDGET *widget, SDL_Renderer *renderer) {
    return createButton(125, PAGE_MARGIN, "./img/new_game.bmp", renderer, widget);
}

int createLoadGameButton(WIDGET *widget, SDL_Renderer *renderer) {
    return createButton(125, PAGE_MARGIN + BUTTON_HEIGHT + BUTTON_MARGIN, "./img/load.bmp", renderer, widget);
}

int createExitButton(WIDGET *widget, SDL_Renderer *renderer) {
    return createButton(125, WINDOW_HEIGHT - PAGE_MARGIN - BUTTON_HEIGHT, "./img/exit.bmp", renderer, widget);
}

GENERIC_WINDOW *welcomeWindowEventHandler (GENERIC_WINDOW *window, SDL_Event *event, CHESS_MATCH *match) {
    GENERIC_WINDOW *nextWindow = window;
    int widgetIndex = getClickedWidget(window, event);
    if (widgetIndex >= 0) { // A widget is clicked

        if (widgetIndex == 0) { // The button clicked is New Game
            destroyWindow(window);
            nextWindow = createGenericWindow(drawSettingsWindow); // OK if NULL

        }

        if (widgetIndex == 1) {
            //TODO: Load game draw
            if (!window->widgets[widgetIndex]->isActive) {
                turnButtonOn(window->widgets[widgetIndex], window->renderer);
            } else {
                turnButtonOff(window->widgets[widgetIndex], window->renderer);
            }
            reRenderWindow(window);
        }

        if (widgetIndex == 2) { // The button clicked is Exit
            return NULL;
        }

    }
    return nextWindow;
}

