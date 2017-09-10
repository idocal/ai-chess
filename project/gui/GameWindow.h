//
// Created by Ido on 9/10/17.
//

#ifndef PROJECT_GAMEWINDOW_H
#define PROJECT_GAMEWINDOW_H

#include "GenericWindow.h"
#include "../GameMoves.h"

#define BOARD_WIDTH 640
#define BOARD_HEIGHT 640
#define PIECE_SIZE 80
#define initialX WINDOW_WIDTH - PAGE_MARGIN - BOARD_WIDTH
#define initialBlackY PAGE_MARGIN
#define initialWhiteY PAGE_MARGIN + BOARD_WIDTH - PIECE_SIZE

int drawGameWindow(GENERIC_WINDOW *genericWindow);

int createBoard(WIDGET *widget, SDL_Renderer *renderer);
int createRestartButton(WIDGET *widget, SDL_Renderer *renderer);
int createSaveButton(WIDGET *widget, SDL_Renderer *renderer);
int createLoadButton(WIDGET *widget, SDL_Renderer *renderer);
int createUndoButton(WIDGET *widget, SDL_Renderer *renderer);
int createMenuButton(WIDGET *widget, SDL_Renderer *renderer);

EVENT_RESPONSE *gameWindowEventHandler(GENERIC_WINDOW *window, SDL_Event *event, CHESS_MATCH *match);

#endif //PROJECT_GAMEWINDOW_H
