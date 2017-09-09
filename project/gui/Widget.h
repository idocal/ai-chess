//
// Created by Ido on 9/9/17.
//

#ifndef PROJECT_WIDGET_H
#define PROJECT_WIDGET_H

#include <SDL.h>
#include <SDL_video.h>

#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 100

typedef struct widget {
    SDL_Rect rect;
    SDL_Texture *texture;
    int (*handleEvent) (SDL_Event *event);
} Widget;

Widget *createWidget(int(*createWidgetFunc)(Widget *widget, SDL_Renderer *renderer), SDL_Renderer *);

void destroyWidget(Widget *widget);

#endif //PROJECT_WIDGET_H
