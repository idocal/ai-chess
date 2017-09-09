//
// Created by Ido on 9/9/17.
//

#ifndef PROJECT_WIDGET_H
#define PROJECT_WIDGET_H

#include <SDL.h>
#include <SDL_video.h>
#include "../MatchManagement.h"
#include "GenericWindow.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define NARROW_WINDOW_WIDTH 550
#define COLOR_WHITE 255, 255, 255, 1

#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 100
#define BUTTON_MARGIN 15
#define PAGE_MARGIN 64
#define TITLE_WIDTH 530
#define TITLE_HEIGHT 40

typedef struct widget {
    SDL_Rect rect;
    SDL_Texture *texture;
    GENERIC_WINDOW * (*handleEvent) (SDL_Event *event, GENERIC_WINDOW *window, CHESS_MATCH *match);
    char imgPath[1024];
} WIDGET;

WIDGET *createWidget(int(*createWidgetFunc)(WIDGET *widget, SDL_Renderer *renderer), SDL_Renderer *);

void destroyWidget(WIDGET *widget);

int createButton(int x, int y, char *imgPath, int (*eventHandler) (SDL_Event *event), SDL_Renderer *renderer, WIDGET *widget);
int createTitle(char *imgPath, SDL_Renderer *renderer, WIDGET *widget);

#endif //PROJECT_WIDGET_H
