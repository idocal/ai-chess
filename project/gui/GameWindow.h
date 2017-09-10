//
// Created by Ido on 9/10/17.
//

#ifndef PROJECT_GAMEWINDOW_H
#define PROJECT_GAMEWINDOW_H

#include "GenericWindow.h"
#include "../GameMoves.h"

int drawGameWindow(GENERIC_WINDOW *genericWindow);

int createBoard(WIDGET *widget, SDL_Renderer *renderer);
int createRestartButton(WIDGET *widget, SDL_Renderer *renderer);
int createSaveButton(WIDGET *widget, SDL_Renderer *renderer);
int createLoadButton(WIDGET *widget, SDL_Renderer *renderer);
int createUndoButton(WIDGET *widget, SDL_Renderer *renderer);
int createMenuButton(WIDGET *widget, SDL_Renderer *renderer);
int createPiece(WIDGET *widget, SDL_Renderer *renderer, char piece);

EVENT_RESPONSE *gameWindowEventHandler(GENERIC_WINDOW *window, SDL_Event *event, CHESS_MATCH *match);

#endif //PROJECT_GAMEWINDOW_H
