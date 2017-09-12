//
// Created by Ido on 9/9/17.
//

#include "WelcomeWindow.h"

int drawWelcomeWindow(GENERIC_WINDOW *genericWindow, SDL_Window *sdlWindow, SDL_Renderer *renderer) {
    unsigned numWidgets = 3;
    genericWindow->numWidgets = numWidgets;
    genericWindow->type = WELCOME_WINDOW;
    genericWindow->handleWindowEvent = (void *) welcomeWindowEventHandler;

    // Assign the application window and renderer
    genericWindow->window = sdlWindow;
    genericWindow->renderer = renderer;

    WIDGET **widgets = (WIDGET **) calloc(numWidgets, sizeof(WIDGET *));
    if (widgets == NULL) {
        destroyWindow(genericWindow);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
        return -1;
    }
    genericWindow->widgets = widgets;

    // Load widgets into widgets array
    widgets[0] = createWidget(createNewGameButton, renderer);
    if (widgets[0] == NULL) {
        destroyWindow(genericWindow);
        free(widgets);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
        return -1;
    }

    widgets[1] = createWidget(createLoadWelcomeButton, renderer);
    if (widgets[1] == NULL) {
        destroyWindow(genericWindow);
        free(widgets);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
        return -1;
    }
    widgets[2] = createWidget(createExitWelcomeButton, renderer);
    if (widgets[2] == NULL) {
        destroyWindow(genericWindow);
        free(widgets);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
        return -1;
    }

    reRenderWindow(genericWindow);

    return 1;
}

int createNewGameButton(WIDGET *widget, SDL_Renderer *renderer) {
    return createButton(WELCOME_WINDOW_MIDDLE_X_POS, PAGE_MARGIN, "./img/new_game.bmp", renderer, widget, false);
}

int createLoadWelcomeButton(WIDGET *widget, SDL_Renderer *renderer) {
    return createButton(WELCOME_WINDOW_MIDDLE_X_POS, PAGE_MARGIN + BUTTON_HEIGHT + BUTTON_MARGIN, "./img/load.bmp", renderer, widget, false);
}

int createExitWelcomeButton(WIDGET *widget, SDL_Renderer *renderer) {
    return createButton(WELCOME_WINDOW_MIDDLE_X_POS, WINDOW_HEIGHT - PAGE_MARGIN - BUTTON_HEIGHT, "./img/exit.bmp", renderer, widget, false);
}



EVENT_RESPONSE *welcomeWindowEventHandler(GENERIC_WINDOW *window, SDL_Event *event, CHESS_MATCH *match, MOVES_STACK *stack) {
    GENERIC_WINDOW *nextWindow = window;
    int widgetIndex = getClickedWidget(window, event);
    SDL_Renderer *renderer = window->renderer;
    EVENT_RESPONSE *response = createEventResponse(window, SAME_WINDOW);

    if (widgetIndex == 0) { // The button clicked is New Game
        nextWindow = createGenericWindow(drawSettingsWindow, nextWindow->window, renderer); // OK if NULL
        response = createEventResponse(nextWindow, NEW_WINDOW);
    }

    if (widgetIndex == 1) { // The button clicked is Load Game
        nextWindow = createGenericWindow(drawLoadGameWindow, nextWindow->window, renderer);
        response = createEventResponse(nextWindow, NEW_WINDOW);
    }

    if (widgetIndex == 2) { // The button clicked is Exit
        response->status = EXIT_WINDOW; // NULL window determines exiting
    }

    return response;
}

