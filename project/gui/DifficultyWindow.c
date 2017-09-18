//
// Created by Ido on 9/10/17.
//

#include "DifficultyWindow.h"


int drawDifficultyWindow(GENERIC_WINDOW *genericWindow, SDL_Window *sdlWindow, SDL_Renderer *renderer, CHESS_MATCH *match) {
    unsigned numWidgets = 8;
    genericWindow->numWidgets = numWidgets;
    int numWidgetsCreated = 0;
    genericWindow->type = SETTINGS_DIFFICULTY_WINDOW;
    genericWindow->handleWindowEvent = difficultyWindowEventHandler;

    // Assign the application window and renderer
    genericWindow->window = sdlWindow;
    genericWindow->renderer = renderer;


    WIDGET **widgets = (WIDGET **) calloc(numWidgets, sizeof(void *));
    if (widgets == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
    genericWindow->widgets = widgets;

    // Load widgets into widgets array
    widgets[0] = createWidget(createDifficultyTitle, renderer);
    if (widgets[0] == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
    numWidgetsCreated++;

    widgets[1] = createWidget(createNoobButton, renderer);
    if (widgets[1] == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
    numWidgetsCreated++;

    widgets[2] = createWidget(createEasyButton, renderer);
    if (widgets[2] == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
    numWidgetsCreated++;

    widgets[3] = createWidget(createModerateButton, renderer);
    if (widgets[3] == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
    numWidgetsCreated++;

    widgets[4] = createWidget(createHardButton, renderer);
    if (widgets[4] == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
    numWidgetsCreated++;

    widgets[5] = createWidget(createExpertButton, renderer);
    if (widgets[5] == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
    numWidgetsCreated++;

    widgets[6] = createWidget(createBackButton, renderer);
    if (widgets[6] == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
    numWidgetsCreated++;

    widgets[7] = createWidget(createNextButton, renderer);
    if (widgets[7] == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
    numWidgetsCreated++;

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
    WINDOW_TYPE nextWindow = SETTINGS_DIFFICULTY_WINDOW;
    int widgetIndex = getClickedWidget(window, event);
    WIDGET *widget = window->widgets[widgetIndex];
    SDL_Renderer *renderer = window->renderer;
    EVENT_RESPONSE *response = createEventResponse(nextWindow, SAME_WINDOW);

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
        response->windowType = SETTINGS_COLOR_WINDOW;
        response->status = NEW_WINDOW;
    }

    return response;
}

