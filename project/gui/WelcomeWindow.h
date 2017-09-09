//
// Created by Ido on 9/9/17.
//

#ifndef PROJECT_WELCOMEWINDOW_H
#define PROJECT_WELCOMEWINDOW_H

#include "GenericWindow.h"
#define COLOR_WHITE 255, 255, 255, 1

int drawWelcomeWindow(GENERIC_WINDOW *genericWindow);

int createNewGameButton(WIDGET *widget, SDL_Renderer *renderer);
int newGameEventHandler(SDL_Event *event);

int createLoadGameButton(WIDGET *widget, SDL_Renderer *renderer);

int createExitButton(WIDGET *widget, SDL_Renderer *renderer);


#endif //PROJECT_WELCOMEWINDOW_H
