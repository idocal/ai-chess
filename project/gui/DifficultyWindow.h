//
// Created by Ido on 9/10/17.
//

#ifndef PROJECT_DIFFICULTYWINDOW_H
#define PROJECT_DIFFICULTYWINDOW_H

#include "GenericWindow.h"
#include "../MatchManagement.h"

int drawDifficultyWindow(GENERIC_WINDOW *genericWindow);

int createDifficultyTitle(WIDGET *widget, SDL_Renderer *renderer);
int createNoobButton(WIDGET *widget, SDL_Renderer *renderer);
int createEasyButton(WIDGET *widget, SDL_Renderer *renderer);
int createModerateButton(WIDGET *widget, SDL_Renderer *renderer);
int createHardButton(WIDGET *widget, SDL_Renderer *renderer);
int createExpertButton(WIDGET *widget, SDL_Renderer *renderer);

EVENT_RESPONSE * difficultyWindowEventHandler(GENERIC_WINDOW *window, SDL_Event *event, CHESS_MATCH *match);

#endif //PROJECT_DIFFICULTYWINDOW_H
