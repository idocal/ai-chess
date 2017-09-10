//
// Created by Ido on 9/9/17.
//

#ifndef PROJECT_WIDGET_H
#define PROJECT_WIDGET_H

#include <SDL.h>
#include <SDL_video.h>
#include <stdbool.h>

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
    char imgPath[1024];
    bool isActive;
    bool isEnable;
} WIDGET;

WIDGET *createWidget(int(*createWidgetFunc)(WIDGET *widget, SDL_Renderer *renderer), SDL_Renderer *);

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

#endif //PROJECT_WIDGET_H
