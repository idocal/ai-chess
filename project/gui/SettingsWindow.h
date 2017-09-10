//
// Created by Ido on 9/9/17.
//

#ifndef PROJECT_SETTINGSMODEWINDOW_H
#define PROJECT_SETTINGSMODEWINDOW_H

#include "GenericWindow.h"
#include "../MatchManagement.h"

int drawSettingsWindow(GENERIC_WINDOW *genericWindow);

int createGameModeTitle(WIDGET *widget, SDL_Renderer *renderer);
int createOnePlayerButton(WIDGET *widget, SDL_Renderer *renderer);
int createTwoPlayersButton(WIDGET *widget, SDL_Renderer *renderer);
int createBackButton(WIDGET *widget, SDL_Renderer *renderer);
int createStartButton(WIDGET *widget, SDL_Renderer *renderer);
int createNextButton(WIDGET *widget, SDL_Renderer *renderer);

int onePlayerEventHandler(SDL_Event *event, CHESS_MATCH *match);
int twoPlayersEventHandler(SDL_Event *event, CHESS_MATCH *match);
int backEventHandler(SDL_Event *event, CHESS_MATCH *match);
int startEventHandler(SDL_Event *event, CHESS_MATCH *match);
int nextEventHandler(SDL_Event *event, CHESS_MATCH *match);



#endif //PROJECT_SETTINGSMODEWINDOW_H