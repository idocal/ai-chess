//
// Created by Ido on 9/9/17.
//

#ifndef PROJECT_WELCOMEWINDOW_H
#define PROJECT_WELCOMEWINDOW_H

#include "GenericWindow.h"
#define COLOR_WHITE 255, 255, 255, 1

int drawWelcomeWindow(GenericWindow *genericWindow);

int createNewGameButton(Widget *widget, SDL_Renderer *renderer);
int newGameEventHandler(SDL_Event *event);

int createLoadGameButton(Widget *widget, SDL_Renderer *renderer);

int createExitButton(Widget *widget, SDL_Renderer *renderer);


#endif //PROJECT_WELCOMEWINDOW_H
