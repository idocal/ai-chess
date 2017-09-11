//
// Created by Ido on 9/9/17.
//

#ifndef PROJECT_GENERICWINDOW_H
#define PROJECT_GENERICWINDOW_H

#include <SDL.h>
#include <SDL_video.h>
#include "../GameAux.h"
#include "Widget.h"

typedef enum {
    WELCOME_WINDOW,
    GAME_WINDOW,
    LOAD_WINDOW,
    SETTINGS_MODE_WINDOW,
    SETTINGS_DIFFICULTY_WINDOW,
    SETTINGS_COLOR_WINDOW
} WINDOW_TYPE;

typedef struct generic_window {
    SDL_Window *window;
    SDL_Renderer *renderer;
    WIDGET **widgets;
    int numWidgets;
    WINDOW_TYPE type;
    void *(*handleWindowEvent)(struct generic_window *, SDL_Event *event, CHESS_MATCH *match, MOVES_STACK *stack);
} GENERIC_WINDOW;

typedef enum {
    NEW_WINDOW,
    SAME_WINDOW,
    BACK_WINDOW,
    EXIT_WINDOW,
    NO_STATUS
} RESPONSE_STATUS;

typedef struct eventResponse {
    GENERIC_WINDOW *window;
    RESPONSE_STATUS status;
} EVENT_RESPONSE;

GENERIC_WINDOW *createGenericWindow(int(*drawFunc)(GENERIC_WINDOW* genericWindow, SDL_Window *sdlWindow, SDL_Renderer *renderer),
                                    SDL_Window *, SDL_Renderer *);

void destroyWindow(GENERIC_WINDOW *);

int detectWidgetByLocation(GENERIC_WINDOW *window, int x, int y);

// Common buttons event handlers
int exitEventHandler(SDL_Event *event);

int loadGameEventHandler(SDL_Event *event);

int getClickedWidget(GENERIC_WINDOW *window, SDL_Event *event);

void renderWindowWidgets(GENERIC_WINDOW *window);

void reRenderWindow(GENERIC_WINDOW *window);

// Event handler response to GUI Manager
EVENT_RESPONSE *createEventResponse(GENERIC_WINDOW *window, RESPONSE_STATUS status);

void destroyEventResponse(EVENT_RESPONSE *);

int findActiveButton(GENERIC_WINDOW *window);

#endif //PROJECT_GENERICWINDOW_H
