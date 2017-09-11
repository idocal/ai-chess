//
// Created by Ido on 9/9/17.
//

#ifndef PROJECT_SETTINGSMODEWINDOW_H
#define PROJECT_SETTINGSMODEWINDOW_H

#include "GenericWindow.h"
#include "DifficultyWindow.h"
#include "../MatchManagement.h"

int drawSettingsWindow(GENERIC_WINDOW *genericWindow, SDL_Window *sdlWindow, SDL_Renderer *renderer);

int createGameModeTitle(WIDGET *widget, SDL_Renderer *renderer);
int createOnePlayerButton(WIDGET *widget, SDL_Renderer *renderer);
int createTwoPlayersButton(WIDGET *widget, SDL_Renderer *renderer);
int createBackButton(WIDGET *widget, SDL_Renderer *renderer);
int createStartButton(WIDGET *widget, SDL_Renderer *renderer);
int createNextButton(WIDGET *widget, SDL_Renderer *renderer);

EVENT_RESPONSE *settingsWindowEventHandler(GENERIC_WINDOW *window, SDL_Event *event, CHESS_MATCH *match, MOVES_STACK *stack);

#endif //PROJECT_SETTINGSMODEWINDOW_H
