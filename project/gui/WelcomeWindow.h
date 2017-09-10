//
// Created by Ido on 9/9/17.
//

#ifndef PROJECT_WELCOMEWINDOW_H
#define PROJECT_WELCOMEWINDOW_H

#include "GenericWindow.h"
#include "SettingsWindow.h"

typedef enum welcomeWidget {
    WELCOME_NEW_GAME,
    WELCOME_LOAD_GAME,
    WELCOME_EXIT,
    WELCOME_NONE
} WELCOME_WIDGET;

int drawWelcomeWindow(GENERIC_WINDOW *genericWindow);

int createNewGameButton(WIDGET *widget, SDL_Renderer *renderer);
GENERIC_WINDOW *newGameEventHandler(SDL_Event *event, GENERIC_WINDOW *window, CHESS_MATCH *match);

int createLoadGameButton(WIDGET *widget, SDL_Renderer *renderer);

int createExitButton(WIDGET *widget, SDL_Renderer *renderer);

EVENT_RESPONSE * welcomeWindowEventHandler(GENERIC_WINDOW *window, SDL_Event *event, CHESS_MATCH *match);

#endif //PROJECT_WELCOMEWINDOW_H
