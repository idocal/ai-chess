//
// Created by Ido on 9/9/17.
//

#include "WelcomeWindow.h"

int drawWelcomeWindow(GENERIC_WINDOW *genericWindow) {
    int numWidgets = 3;
    genericWindow->numWidgets = numWidgets;
    genericWindow->type = WELCOME_WINDOW;

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

    SDL_SetRenderDrawColor(renderer, COLOR_WHITE);
    SDL_RenderClear(renderer);

    // Place images on screen
    for (int i = 0; i < numWidgets; ++i) {
        SDL_RenderCopy(renderer, widgets[i]->texture, NULL, &(widgets[i]->rect));
    }

    SDL_RenderPresent(renderer);

    return 1;
}

int createNewGameButton(WIDGET *widget, SDL_Renderer *renderer) {
    return createButton(125, PAGE_MARGIN, "./img/new_game.bmp", newGameEventHandler, renderer, widget);
}

int createLoadGameButton(WIDGET *widget, SDL_Renderer *renderer) {
    return createButton(125, PAGE_MARGIN + BUTTON_HEIGHT + BUTTON_MARGIN, "./img/load.bmp", loadGameEventHandler, renderer, widget);
}

int createExitButton(WIDGET *widget, SDL_Renderer *renderer) {
    return createButton(125, WINDOW_HEIGHT - PAGE_MARGIN - BUTTON_HEIGHT, "./img/exit.bmp", loadGameEventHandler, renderer, widget);
}

GENERIC_WINDOW *newGameEventHandler(SDL_Event *event, GENERIC_WINDOW *window, CHESS_MATCH *match) {
    if (event->type == SDL_MOUSEBUTTONUP) {

    } else if (event->type == SDL_MOUSEBUTTONDOWN) {
        destroyWindow(window);
        return createGenericWindow(drawSettingsWindow); // OK if NULL
    }
}
