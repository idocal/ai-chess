//
// Created by okleinfeld on 9/11/17.
//

#include "LoadGamesWindow.h"

int drawLoadGameWindow(GENERIC_WINDOW *genericWindow, SDL_Window *sdlWindow, SDL_Renderer *renderer){
    unsigned numFiles = getNumSavedFilesInGameDir();
    if (numFiles == -1){
        return -1;
    }
    unsigned numWidgets = numFiles + 2; // extra back and load buttons
    genericWindow->numWidgets = numWidgets;
    genericWindow->type = SETTINGS_MODE_WINDOW;
    genericWindow->handleWindowEvent = (void *) loadGameEventHandler;

    // Assign application's window and renderer
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
    // back and load buttons always exist. we'll denote them widget 0 and 1 respectively
    widgets[0] = createWidget(createBackButton, renderer);
    if (widgets[0] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
        return -1;
    }

    widgets[1] = createWidget(createLoadGameButton, renderer);
    if (widgets[1] == NULL) {
        SDL_DestroyRenderer(renderer);
        free(widgets);
        genericWindow->window = NULL;
        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
        return -1;
    }
}






int createLoadGameButton(WIDGET *widget, SDL_Renderer *renderer) {
    int x = (WINDOW_WIDTH - (2 * BUTTON_WIDTH + BUTTON_MARGIN)) / 2 + BUTTON_WIDTH + BUTTON_MARGIN;
    int y = WINDOW_HEIGHT - PAGE_MARGIN - BUTTON_HEIGHT;
    return createButton(x, y, "./img/load.bmp", renderer, widget, false);
}


int getNumSavedFilesInGameDir(){
    struct dirent *dirEntry; // Pointer to the directory entry
    DIR *directory = opendir("saved_games"); // Pointer to a directory object
    if (directory == NULL){
        return -1;
    }
    int filesCounter = 0;
    while ((dirEntry = readdir(directory)) != NULL){ // more files in the directory
        filesCounter++;
    }
    closedir(directory);
    filesCounter -= 2; // a subdirectory is also an entry so the functions counts also "./" and '../" as entries
    return filesCounter;
}

