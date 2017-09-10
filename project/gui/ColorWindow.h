//
// Created by Ido on 9/10/17.
//

#ifndef PROJECT_COLORWINDOW_H
#define PROJECT_COLORWINDOW_H

#include "GenericWindow.h"
#include "../MatchManagement.h"

int drawColorWindow(GENERIC_WINDOW *genericWindow);

int createColorTitle(WIDGET *widget, SDL_Renderer *renderer);
int createWhiteButton(WIDGET *widget, SDL_Renderer *renderer);
int createBlackButton(WIDGET *widget, SDL_Renderer *renderer);

EVENT_RESPONSE *colorWindowEventHandler(GENERIC_WINDOW *window, SDL_Event *event, CHESS_MATCH *match);

#endif //PROJECT_COLORWINDOW_H
