//
// Created by Ido on 9/9/17.
//

#ifndef PROJECT_WIDGET_H
#define PROJECT_WIDGET_H

#include <SDL.h>
#include <SDL_video.h>

#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 100
#define BUTTON_MARGIN 15
#define PAGE_MARGIN 64

typedef struct widget {
    SDL_Rect rect;
    SDL_Texture *texture;
    int (*handleEvent) (SDL_Event *event);
    char imgPath[1024];
} WIDGET;

WIDGET *createWidget(int(*createWidgetFunc)(WIDGET *widget, SDL_Renderer *renderer), SDL_Renderer *);

void destroyWidget(WIDGET *widget);

int createButton(int x, int y, char *imgPath, int (*eventHandler) (SDL_Event *event), SDL_Renderer *renderer, WIDGET *widget);

#endif //PROJECT_WIDGET_H
