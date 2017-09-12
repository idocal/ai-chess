//
// Created by Ido on 9/9/17.
//

#ifndef PROJECT_WIDGET_H
#define PROJECT_WIDGET_H

#include <SDL.h>
#include <SDL_video.h>
#include <stdbool.h>
#include "config.h"


typedef struct boardPosition {
    int row;
    int col;
} BOARD_POSITION;

typedef struct widget {
    SDL_Rect rect;
    SDL_Texture *texture;
    BOARD_POSITION *position;
    char imgPath[1024];
    bool isActive;
    bool isEnable;
    char color; // 0 is black, 1 is white
    char piece;
    bool isClickable;
} WIDGET;

BOARD_POSITION *createBoardPosition(int row, int col); // destroy unnecessary - use free().

WIDGET *createWidget(int(*createWidgetFunc)(WIDGET *widget, SDL_Renderer *renderer), SDL_Renderer *);

WIDGET *createGameSlotWidget(int(*createWidgetFunc)(WIDGET *, SDL_Renderer *, int), SDL_Renderer *renderer, int slotNum);

void destroyWidget(WIDGET *widget);

int createButton(int x, int y, char *imgPath, SDL_Renderer *renderer, WIDGET *widget, bool isActive);
int createTitle(char *imgPath, SDL_Renderer *renderer, WIDGET *widget);
int createBackground(int x, int y, int w, int h, char *imgPath, SDL_Renderer *renderer, WIDGET *widget);
int createPieceGUI(int x, int y, char piece, SDL_Renderer *renderer, WIDGET *widget);

void toggleButton(WIDGET *widget, SDL_Renderer *renderer);
void toggleButtonAbility(WIDGET *widget, SDL_Renderer *renderer);

// Common buttons
int createBackButton(WIDGET *widget, SDL_Renderer *renderer);
int createStartButton(WIDGET *widget, SDL_Renderer *renderer);
int createNextButton(WIDGET *widget, SDL_Renderer *renderer);

BOARD_POSITION *calculateBoardPosition(int x, int y);

#endif //PROJECT_WIDGET_H
