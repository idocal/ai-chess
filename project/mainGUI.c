#include "mainGUI.h"


int mainGui() {
    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf(SDL_ERROR_PREFIX, SDL_GetError());
        return 1;
    };

    // Create SDL Window
    SDL_Window *window = SDL_CreateWindow("chess game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    if (window == NULL) {
        SDL_Quit();
        return -1;
    }

    // Create renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Create GUI manager
    GUI_MANAGER *manager = createManager(window, renderer);
    if (manager == NULL) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }

    // Wait for events in a loop and deal with manager handler
    SDL_Event event;
    while (1) {
        SDL_WaitEvent(&event);
        if (managerEventHandler(manager, &event) == MANAGER_QUIT) break;
    }

    // GUI quit
    destroyManager(manager);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
