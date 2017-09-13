//
// Created by Ido on 9/9/17.
//

#include "SettingsWindow.h"


int drawSettingsWindow(GENERIC_WINDOW *genericWindow, SDL_Window *sdlWindow, SDL_Renderer *renderer, CHESS_MATCH *match) {
    unsigned numWidgets = 5;
    genericWindow->numWidgets = numWidgets;
    int numWidgetsCreated = 0;
    genericWindow->type = SETTINGS_MODE_WINDOW;
    genericWindow->handleWindowEvent = (void *) settingsWindowEventHandler;

    // Assign application's window and renderer
    genericWindow->window = sdlWindow;
    genericWindow->renderer = renderer;

    WIDGET **widgets = (WIDGET **) calloc(numWidgets, sizeof(WIDGET *));
    if (widgets == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
    genericWindow->widgets = widgets;

    // Load widgets into widgets array
    widgets[0] = createWidget(createGameModeTitle, renderer);
    if (widgets[0] == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
    numWidgetsCreated++;

    widgets[1] = createWidget(createOnePlayerButton, renderer);
    if (widgets[1] == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
    numWidgetsCreated++;

    widgets[2] = createWidget(createTwoPlayersButton, renderer);
    if (widgets[2] == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
    numWidgetsCreated++;

    widgets[3] = createWidget(createBackButton, renderer);
    if (widgets[3] == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
    numWidgetsCreated++;

    widgets[4] = createWidget(createNextButton, renderer);
    if (widgets[4] == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
    numWidgetsCreated++;

    reRenderWindow(genericWindow);

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

EVENT_RESPONSE *settingsWindowEventHandler(GENERIC_WINDOW *window, SDL_Event *event, CHESS_MATCH *match, MOVES_STACK *stack) {
    WINDOW_TYPE nextWindow = SETTINGS_MODE_WINDOW;
    int widgetIndex = getClickedWidget(window, event);
    WIDGET *widget = window->widgets[widgetIndex];
    SDL_Renderer *renderer = window->renderer;
    EVENT_RESPONSE *response = createEventResponse(nextWindow, SAME_WINDOW);

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

    if (widgetIndex == 3) { // The button clicked is Back
        response->status = BACK_WINDOW;
    }

    if (widgetIndex == 4) { // The button clicked is Next / Start
        if (match->gameMode == 1) { // One player mode -> go to Next
            response->windowType = SETTINGS_DIFFICULTY_WINDOW;
        } else { // Two players mode -> go to Game
            response->windowType = GAME_WINDOW;
        }
        response->status = NEW_WINDOW;
    }

    return response;
}
