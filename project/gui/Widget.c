//
// Created by Ido on 9/9/17.
//

#include "Widget.h"
Widget *createWidget(int(*createWidgetFunc)(Widget *, SDL_Renderer *), SDL_Renderer *renderer) {
    Widget *widget = calloc(sizeof(Widget), sizeof(char));
    if (widget == NULL) return NULL;

    int res = (*createWidgetFunc)(widget, renderer);
    if (res == -1) return NULL;

    return widget;
}

void destroyWidget(Widget *widget) {
    SDL_DestroyTexture(widget->texture);
    free(widget);
}

int createButton(int x, int y, char *imgPath, int (*eventHandler) (SDL_Event *event), SDL_Renderer *renderer, Widget *widget) {
    SDL_Surface *loadingSurface = NULL;
    strcpy(widget->imgPath, imgPath);

    // Widget rect
    SDL_Rect rect = {.x = x, .y = y, .w = BUTTON_WIDTH, .h = BUTTON_HEIGHT};
    widget->rect = rect;

    // Widget surface, used to create texture and then destroyed
    loadingSurface = SDL_LoadBMP(imgPath);
    if (loadingSurface == NULL) return -1;

    // Widget texture
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
    if (texture == NULL) {
        SDL_FreeSurface(loadingSurface);
        return -1;
    }
    widget->texture = texture;

    SDL_FreeSurface(loadingSurface);

    // Handle events
    widget->handleEvent = eventHandler;
    return 1;
}