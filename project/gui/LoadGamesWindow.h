//
// Created by okleinfeld on 9/11/17.
//

#ifndef PROJECT_LOADGAMES_H
#define PROJECT_LOADGAMES_H

#include "GenericWindow.h"
#include "GameWindow.h"
#include "../MatchManagement.h"
#include <dirent.h>

#define WINDOW_MIDDLE_X_POS (WINDOW_WIDTH - BUTTON_WIDTH) / 2

int drawLoadGameWindow(GENERIC_WINDOW *genericWindow, SDL_Window *sdlWindow, SDL_Renderer *renderer);


int createLoadGameButton(WIDGET *widget, SDL_Renderer *renderer);

int createGameSlotButton(WIDGET *widget, SDL_Renderer *renderer, int slotNum);

EVENT_RESPONSE *loadGameWindowEventHandler(GENERIC_WINDOW *window, SDL_Event *event, CHESS_MATCH *match, MOVES_STACK *stack);

// Util functions

int getNumSavedFilesInGameDir();

void getGameSlotButtonPath(char *allocStr, int slotNum);

int getGameSlotButtonYposition(int slotNum);

#endif //PROJECT_LOADGAMES_H

