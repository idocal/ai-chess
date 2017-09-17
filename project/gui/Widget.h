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

/**
 * Creates a board position
 * @param row
 * @param col
 * @return A ptr to the created position
 */
BOARD_POSITION *createBoardPosition(int row, int col); // destroy unnecessary - use free().

/**
 * Creates a widget using its creation function
 * @param createWidgetFunc
 * @return A ptr to the created widget
 */
WIDGET *createWidget(int(*createWidgetFunc)(WIDGET *widget, SDL_Renderer *renderer), SDL_Renderer *);

/**
 * Creates a game slot widget, which is somewhat different than a normal widget
 * @param createWidgetFunc
 * @param renderer
 * @param slotNum
 * @return A ptr to the created widget
 */
WIDGET *createGameSlotWidget(int(*createWidgetFunc)(WIDGET *, SDL_Renderer *, int), SDL_Renderer *renderer, int slotNum);

/**
 * Destroys a certain widget
 * @param widget
 */
void destroyWidget(WIDGET *widget);

/**
 * Creates a generic button
 * @param x
 * @param y
 * @param imgPath
 * @param renderer
 * @param widget
 * @param isActive
 * @return 1 on success
 */
int createButton(int x, int y, char *imgPath, SDL_Renderer *renderer, WIDGET *widget, bool isActive);

/**
 * Creates a generic disabled button
 * @param x
 * @param y
 * @param imgPath
 * @param renderer
 * @param widget
 * @param isActive
 * @return 1 on success
 */
int createDisabledButton(int x, int y, char *imgPath, SDL_Renderer *renderer, WIDGET *widget, bool isActive);

/**
 * Creates a generic window title
 * @param imgPath
 * @param renderer
 * @param widget
 * @return 1 on success
 */
int createTitle(char *imgPath, SDL_Renderer *renderer, WIDGET *widget);

/**
 * Creates a generic background widget
 * @param x
 * @param y
 * @param w
 * @param h
 * @param imgPath
 * @param renderer
 * @param widget
 * @return 1 on success
 */
int createBackground(int x, int y, int w, int h, char *imgPath, SDL_Renderer *renderer, WIDGET *widget);

/**
 * Creates a GUI widget
 * @param x
 * @param y
 * @param piece
 * @param renderer
 * @return A ptr to the created widget
 */
WIDGET * createPieceGUI(int x, int y, char piece, SDL_Renderer *renderer);

/**
 * Creates a "get moves" bonus colored cell
 * @param x
 * @param y
 * @param renderer
 * @param moveType
 * @return A ptr to the created widget
 */
WIDGET *createMoveCell(int x, int y, SDL_Renderer *renderer, char moveType);

/**
 * Toggles activity of a button (active, inactive)
 * @param widget
 * @param renderer
 */
void toggleButton(WIDGET *widget, SDL_Renderer *renderer);

/**
 * Toggles ability of a button (enabled, disabled)
 * @param widget
 * @param renderer
 */
void toggleButtonAbility(WIDGET *widget, SDL_Renderer *renderer);

// Common buttons
int createBackButton(WIDGET *widget, SDL_Renderer *renderer);
int createStartButton(WIDGET *widget, SDL_Renderer *renderer);
int createNextButton(WIDGET *widget, SDL_Renderer *renderer);

/**
 * Calcualtes the board position according to screen position <x,y>
 * @param x
 * @param y
 * @return A ptr to the calculated board position
 */
BOARD_POSITION *calculateBoardPosition(int x, int y);

#endif //PROJECT_WIDGET_H
