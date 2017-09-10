//
// Created by Ido on 9/9/17.
//

#include "SettingsWindow.h"


int drawSettingsWindow(GENERIC_WINDOW *genericWindow) {
    int numWidgets = 5;
    genericWindow->numWidgets = numWidgets;
    genericWindow->type = SETTINGS_MODE_WINDOW;
    genericWindow->handleWindowEvent = settingsWindowEventHandler;

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

    // Load widgets into widgets array
    widgets[0] = createWidget(createGameModeTitle, renderer);
    if (widgets[0] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    widgets[1] = createWidget(createOnePlayerButton, renderer);
    if (widgets[1] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    widgets[2] = createWidget(createTwoPlayersButton, renderer);
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

    widgets[4] = createWidget(createNextButton, renderer);
    if (widgets[4] == NULL) {
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

int createGameModeTitle(WIDGET *widget, SDL_Renderer *renderer) {
    return createTitle("./img/game_mode.bmp", renderer, widget);
}

int createOnePlayerButton(WIDGET *widget, SDL_Renderer *renderer) {
    int x = (WINDOW_WIDTH - (2 * BUTTON_WIDTH + BUTTON_MARGIN)) / 2;
    return createButton(x, 180, "./img/one_player_on.bmp", renderer, widget, true);
}

int createTwoPlayersButton(WIDGET *widget, SDL_Renderer *renderer) {
    int x = (WINDOW_WIDTH - (2 * BUTTON_WIDTH + BUTTON_MARGIN)) / 2 + BUTTON_WIDTH + BUTTON_MARGIN;
    return createButton(x, 180, "./img/two_players.bmp", renderer, widget, false);
}

int createBackButton(WIDGET *widget, SDL_Renderer *renderer) {
    int x = (WINDOW_WIDTH - (2 * BUTTON_WIDTH + BUTTON_MARGIN)) / 2;
    int y = WINDOW_HEIGHT - PAGE_MARGIN - BUTTON_HEIGHT;
    return createButton(x, y, "./img/back.bmp", renderer, widget, false);
}

int createStartButton(WIDGET *widget, SDL_Renderer *renderer) {
    int x = (WINDOW_WIDTH - (2 * BUTTON_WIDTH + BUTTON_MARGIN)) / 2 + BUTTON_WIDTH + BUTTON_MARGIN;
    int y = WINDOW_HEIGHT - PAGE_MARGIN - BUTTON_HEIGHT;
    return createButton(x, y, "./img/start.bmp", renderer, widget, false);
}

int createNextButton(WIDGET *widget, SDL_Renderer *renderer) {
    int x = (WINDOW_WIDTH - (2 * BUTTON_WIDTH + BUTTON_MARGIN)) / 2 + BUTTON_WIDTH + BUTTON_MARGIN;
    int y = WINDOW_HEIGHT - PAGE_MARGIN - BUTTON_HEIGHT;
    return createButton(x, y, "./img/next.bmp", renderer, widget, false);
}

GENERIC_WINDOW *settingsWindowEventHandler (GENERIC_WINDOW *window, SDL_Event *event, CHESS_MATCH *match) {
    GENERIC_WINDOW *nextWindow = window;
    int widgetIndex = getClickedWidget(window, event);
    WIDGET *widget = window->widgets[widgetIndex];
    SDL_Renderer *renderer = window->renderer;

    if (widgetIndex == 1) { // The button clicked is One Player
        if (!widget->isActive) { // If button is inactive - turn it on and toggle the active one
            toggleButton(widget, renderer); // turn one player on
            toggleButton(window->widgets[2], renderer); // turn two players off
            match->gameMode = 1;

            // Swap Next with Start
            WIDGET *removedWidget = window->widgets[4];
            window->widgets[4] = createWidget(createNextButton, renderer);
            destroyWidget(removedWidget);
            reRenderWindow(window);
        }
    }

    if (widgetIndex == 2) { // The button clicked is Two Player
        if (!widget->isActive) { // If button is inactive - turn it on and toggle the active one
            toggleButton(widget, renderer); // turn two players on
            toggleButton(window->widgets[1], renderer); // turn one players off
            match->gameMode = 2;

            // Swap Start with Next
            WIDGET *removedWidget = window->widgets[4];
            window->widgets[4] = createWidget(createStartButton, renderer);
            destroyWidget(removedWidget);
            reRenderWindow(window);
        }
    }

    return nextWindow;
}
