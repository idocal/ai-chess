//
// Created by Ido on 9/9/17.
//

#include "Widget.h"
Widget *createWidget(int(*createWidgetFunc)(Widget *, SDL_Renderer *), SDL_Renderer *renderer) {
    Widget *widget = calloc(sizeof(Widget), sizeof(char));
    if (widget == NULL) return NULL;

    (*createWidgetFunc)(widget, renderer);
    return widget;
}

void destroyWidget(Widget *widget) {
    SDL_DestroyTexture(widget->texture);
    free(widget);
}