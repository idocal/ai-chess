//
// Created by Ido on 9/9/17.
//

#ifndef PROJECT_GENERICWINDOW_H
#define PROJECT_GENERICWINDOW_H

#include <SDL.h>
#include <SDL_video.h>
#include "Widget.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define NARROW_WINDOW_WIDTH 550

typedef struct generic_window {
    SDL_Window *window;
    SDL_Renderer *renderer;
    WIDGET **widgets;
    int numWidgets;
} GENERIC_WINDOW;

GENERIC_WINDOW *createGenericWindow(int(*drawFunc)(GENERIC_WINDOW* window));
void destroyWindow(GENERIC_WINDOW *);

// Common buttons event handlers
int exitEventHandler(SDL_Event *event);
int loadGameEventHandler(SDL_Event *event);

#endif //PROJECT_GENERICWINDOW_H
