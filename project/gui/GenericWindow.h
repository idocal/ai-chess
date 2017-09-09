//
// Created by Ido on 9/9/17.
//

#ifndef PROJECT_GENERICWINDOW_H
#define PROJECT_GENERICWINDOW_H

#include <SDL.h>
#include <SDL_video.h>
#include "Widget.h"

typedef struct generic_window {
    SDL_Window *window;
    SDL_Renderer *renderer;
    Widget **widgets;
    int numWidgets;
    int height;
    int width;
} GenericWindow;

GenericWindow *createGenericWindow(int(*drawFunc)(GenericWindow* window));

#endif //PROJECT_GENERICWINDOW_H
