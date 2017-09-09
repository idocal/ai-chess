//
// Created by Ido on 9/9/17.
//

#include "WelcomeWindow.h"

int drawWelcomeWindow(GenericWindow *genericWindow) {
    int numWidgets = 1;
    genericWindow->numWidgets = numWidgets;

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

    Widget **widgets = calloc(numWidgets, sizeof(Widget *));
    if (widgets == NULL) {
        SDL_DestroyRenderer(renderer);
        genericWindow->window = NULL;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    widgets[0] = createWidget(createNewGameButton, renderer);

    SDL_SetRenderDrawColor(renderer, COLOR_WHITE);
    SDL_RenderClear(renderer);

    // Place images on screen
    for (int i = 0; i < numWidgets; ++i) {
        SDL_RenderCopy(renderer, widgets[i]->texture, NULL, &(widgets[i]->rect));
    }

    SDL_RenderPresent(renderer);

    SDL_Delay(5000);

    return 1;
}

int createNewGameButton(Widget *widget, SDL_Renderer *renderer) {
    SDL_Surface *loadingSurface = NULL;
    // Widget rect
    SDL_Rect rect = {.x = SDL_WINDOWPOS_CENTERED, .y = 64, .w = BUTTON_WIDTH, .h = BUTTON_HEIGHT};
    widget->rect = rect;

    // Widget surface, used to create texture and then destroyed
    loadingSurface = SDL_LoadBMP("./img/new_game.bmp");
    if (loadingSurface == NULL) return -1;

    // Widget texture
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
    if (texture == NULL) {
        SDL_FreeSurface(loadingSurface);
        return -1;
    }

    SDL_FreeSurface(loadingSurface);

    // Handle events
    widget->handleEvent = newGameEventHandler;
    return 1;
}

int newGameEventHandler(SDL_Event *event) {

}