//
// Created by Ido on 9/10/17.
//

#include "DifficultyWindow.h"

int drawDifficultyWindow(GENERIC_WINDOW *genericWindow) {
    int numWidgets = 8;
    genericWindow->numWidgets = numWidgets;
    genericWindow->type = SETTINGS_MODE_WINDOW;
    genericWindow->handleWindowEvent = difficultyWindowEventHandler;

    // Create SDL Window
    SDL_Window *window = SDL_CreateWindow("Difficulty", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
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
    widgets[0] = createWidget(createDifficultyTitle, renderer);
    if (widgets[0] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    widgets[1] = createWidget(createNoobButton, renderer);
    if (widgets[1] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    widgets[2] = createWidget(createEasyButton, renderer);
    if (widgets[2] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    widgets[3] = createWidget(createModerateButton, renderer);
    if (widgets[3] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    widgets[4] = createWidget(createHardButton, renderer);
    if (widgets[4] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    widgets[5] = createWidget(createExpertButton, renderer);
    if (widgets[5] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    widgets[6] = createWidget(createBackButton, renderer);
    if (widgets[6] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    widgets[7] = createWidget(createNextButton, renderer);
    if (widgets[7] == NULL) {
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

int createDifficultyTitle(WIDGET *widget, SDL_Renderer *renderer) {
    return createTitle("./img/difficulty.bmp", renderer, widget);
}

int createNoobButton(WIDGET *widget, SDL_Renderer *renderer) {
    int x = (WINDOW_WIDTH - (3 * BUTTON_WIDTH + 2 * BUTTON_MARGIN)) / 3;
    return createButton(x, 180, "./img/noob.bmp", renderer, widget, false);
}

int createEasyButton(WIDGET *widget, SDL_Renderer *renderer) {
    int x = (WINDOW_WIDTH - (3 * BUTTON_WIDTH + 2 * BUTTON_MARGIN)) / 3 + BUTTON_WIDTH + BUTTON_MARGIN;
    return createButton(x, 180, "./img/easy_on.bmp", renderer, widget, true);
}

int createModerateButton(WIDGET *widget, SDL_Renderer *renderer) {
    int x = (WINDOW_WIDTH - (3 * BUTTON_WIDTH + 2 * BUTTON_MARGIN)) / 3 + 2 * BUTTON_WIDTH + 2 * BUTTON_MARGIN;
    return createButton(x, 180, "./img/moderate.bmp", renderer, widget, false);
}
int createHardButton(WIDGET *widget, SDL_Renderer *renderer) {
    int x = (WINDOW_WIDTH - (2 * BUTTON_WIDTH + BUTTON_MARGIN)) / 2;
    return createButton(x, 180 + BUTTON_HEIGHT + BUTTON_MARGIN, "./img/hard.bmp", renderer, widget, false);
}
int createExpertButton(WIDGET *widget, SDL_Renderer *renderer) {
    int x = (WINDOW_WIDTH - (2 * BUTTON_WIDTH + BUTTON_MARGIN)) / 2 + BUTTON_WIDTH + BUTTON_MARGIN;
    return createButton(x, 180 + BUTTON_HEIGHT + BUTTON_MARGIN, "./img/expert.bmp", renderer, widget, false);
}

GENERIC_WINDOW *difficultyWindowEventHandler (GENERIC_WINDOW *window, SDL_Event *event, CHESS_MATCH *match) {
    return NULL;
}
