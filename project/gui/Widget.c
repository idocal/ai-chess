//
// Created by Ido on 9/9/17.
//

#include "Widget.h"
WIDGET *createWidget(int(*createWidgetFunc)(WIDGET *, SDL_Renderer *), SDL_Renderer *renderer) {
    WIDGET *widget = (WIDGET *) calloc(sizeof(WIDGET), sizeof(char));
    if (widget == NULL) return NULL;

    int res = (*createWidgetFunc)(widget, renderer);
    if (res == -1) return NULL;

    widget->isActive = false;
    return widget;
}

void destroyWidget(WIDGET *widget) {
    if (widget == NULL) return;
    SDL_DestroyTexture(widget->texture);
    free(widget);
}

int createButton(int x, int y, char *imgPath, SDL_Renderer *renderer, WIDGET *widget) {
    SDL_Surface *loadingSurface = NULL;
    strcpy(widget->imgPath, imgPath);

    // WIDGET rect
    SDL_Rect rect = {.x = x, .y = y, .w = BUTTON_WIDTH, .h = BUTTON_HEIGHT};
    widget->rect = rect;

    // WIDGET surface, used to create texture and then destroyed
    loadingSurface = SDL_LoadBMP(imgPath);
    if (loadingSurface == NULL) return -1;

    // WIDGET texture
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
    if (texture == NULL) {
        SDL_FreeSurface(loadingSurface);
        return -1;
    }
    widget->texture = texture;

    SDL_FreeSurface(loadingSurface);

    return 1;
}

int createTitle(char *imgPath, SDL_Renderer *renderer, WIDGET *widget) {
    SDL_Surface *loadingSurface = NULL;
    strcpy(widget->imgPath, imgPath);

    // WIDGET rect
    SDL_Rect rect = {.x = (WINDOW_WIDTH - TITLE_WIDTH) / 2, .y = PAGE_MARGIN, .w = TITLE_WIDTH, .h = TITLE_HEIGHT};
    widget->rect = rect;

    // WIDGET surface, used to create texture and then destroyed
    loadingSurface = SDL_LoadBMP(imgPath);
    if (loadingSurface == NULL) return -1;

    // WIDGET texture
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
    if (texture == NULL) {
        SDL_FreeSurface(loadingSurface);
        return -1;
    }
    widget->texture = texture;

    SDL_FreeSurface(loadingSurface);

    return 1;
}