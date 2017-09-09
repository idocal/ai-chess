//
// Created by Ido on 9/9/17.
//

#include "GenericWindow.h"

GENERIC_WINDOW *createGenericWindow(int(*drawFunc)(GENERIC_WINDOW*)) {
    GENERIC_WINDOW *genericWindow = (GENERIC_WINDOW *) calloc(sizeof(GENERIC_WINDOW), sizeof(char));
    if (genericWindow == NULL) return NULL;

    (*drawFunc)(genericWindow);
    return genericWindow;
}

void destroyWindow(GENERIC_WINDOW *genericWindow) {
    if (genericWindow == NULL) return;

    for (int i = 0; i < genericWindow->numWidgets; ++i) {
        destroyWidget(genericWindow->widgets[i]);
    }
    SDL_DestroyRenderer(genericWindow->renderer);
    SDL_DestroyWindow(genericWindow->window);
    free(genericWindow);
}

int exitEventHandler(SDL_Event *event) {
    return 0;
}

int loadGameEventHandler(SDL_Event *event) {
    return 0;
}