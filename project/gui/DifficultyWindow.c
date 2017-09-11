//
// Created by Ido on 9/10/17.
//

#include "DifficultyWindow.h"


int drawDifficultyWindow(GENERIC_WINDOW *genericWindow, SDL_Window *sdlWindow, SDL_Renderer *renderer) {
    unsigned numWidgets = 8;
    genericWindow->numWidgets = numWidgets;
    genericWindow->type = SETTINGS_DIFFICULTY_WINDOW;
    genericWindow->handleWindowEvent = (void *) difficultyWindowEventHandler;

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

    // Load widgets into widgets array
    widgets[0] = createWidget(createDifficultyTitle, renderer);
    if (widgets[0] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
        return -1;
    }

    widgets[1] = createWidget(createNoobButton, renderer);
    if (widgets[1] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
        return -1;
    }

    widgets[2] = createWidget(createEasyButton, renderer);
    if (widgets[2] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
        return -1;
    }
    widgets[3] = createWidget(createModerateButton, renderer);
    if (widgets[3] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
        return -1;
    }

    widgets[4] = createWidget(createHardButton, renderer);
    if (widgets[4] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
        return -1;
    }

    widgets[5] = createWidget(createExpertButton, renderer);
    if (widgets[5] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
        return -1;
    }

    widgets[6] = createWidget(createBackButton, renderer);
    if (widgets[6] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
        return -1;
    }

    widgets[7] = createWidget(createNextButton, renderer);
    if (widgets[7] == NULL) {
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

EVENT_RESPONSE *difficultyWindowEventHandler(GENERIC_WINDOW *window, SDL_Event *event, CHESS_MATCH *match, MOVES_STACK *stack) {
    GENERIC_WINDOW *nextWindow = window;
    int widgetIndex = getClickedWidget(window, event);
    WIDGET *widget = window->widgets[widgetIndex];
    SDL_Renderer *renderer = window->renderer;
    EVENT_RESPONSE *response = createEventResponse(window, SAME_WINDOW);

    if (widgetIndex >= 1 && widgetIndex <= 5) { // if any difficulty is clicked
        int activeButton = findActiveButton(window);
        if (activeButton == -1) return NULL; // no active button found
        if (activeButton == widgetIndex) return response; // stay in same window if button is active
        else {
            toggleButton(widget, renderer); // activate clicked button
            toggleButton(window->widgets[activeButton], renderer); // deactivate active button
            reRenderWindow(window);
            match->level = widgetIndex;
        }
    }

    if (widgetIndex == 6) { // Back button is clicked
        response->status = BACK_WINDOW;
    }

    if (widgetIndex == 7) { // Next button is clicked
        nextWindow = createGenericWindow(drawColorWindow, nextWindow->window, renderer);
        response->window = nextWindow;
        response->status = NEW_WINDOW;
    }

    return response;
}

