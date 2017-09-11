//
// Created by Ido on 9/10/17.
//

#ifndef PROJECT_GAMEWINDOW_H
#define PROJECT_GAMEWINDOW_H

#include "GameAuxGUI.h"

int drawGameWindow(GENERIC_WINDOW *genericWindow, SDL_Window *, SDL_Renderer *);

int createBoard(WIDGET *widget, SDL_Renderer *renderer);
int createRestartButton(WIDGET *widget, SDL_Renderer *renderer);
int createSaveButton(WIDGET *widget, SDL_Renderer *renderer);
int createLoadButtonGame(WIDGET *widget, SDL_Renderer *renderer);
int createUndoButton(WIDGET *widget, SDL_Renderer *renderer);
int createMenuButton(WIDGET *widget, SDL_Renderer *renderer);
int createExitButtonGame(WIDGET *widget, SDL_Renderer *renderer);

EVENT_RESPONSE *gameWindowEventHandler(GENERIC_WINDOW *window, SDL_Event *event, CHESS_MATCH *match, MOVES_STACK *stack);

#endif //PROJECT_GAMEWINDOW_H
