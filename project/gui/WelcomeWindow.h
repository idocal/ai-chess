//
// Created by Ido on 9/9/17.
//

#ifndef PROJECT_WELCOMEWINDOW_H
#define PROJECT_WELCOMEWINDOW_H

#include "GenericWindow.h"

#define WELCOME_WINDOW_MIDDLE_X_POS (WINDOW_WIDTH - BUTTON_WIDTH) / 2

typedef enum welcomeWidget {
    WELCOME_NEW_GAME,
    WELCOME_LOAD_GAME,
    WELCOME_EXIT,
    WELCOME_NONE
} WELCOME_WIDGET;

int drawWelcomeWindow(GENERIC_WINDOW *genericWindow, SDL_Window *sdlWindow, SDL_Renderer *renderer);

int createNewGameButton(WIDGET *widget, SDL_Renderer *renderer);

int createLoadWelcomeButton(WIDGET *widget, SDL_Renderer *renderer);

int createExitWelcomeButton(WIDGET *widget, SDL_Renderer *renderer);

EVENT_RESPONSE *welcomeWindowEventHandler(GENERIC_WINDOW *window, SDL_Event *event, CHESS_MATCH *match, MOVES_STACK *stack);

#endif //PROJECT_WELCOMEWINDOW_H
