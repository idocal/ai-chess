//
// Created by Ido on 9/9/17.
//

#ifndef PROJECT_GENERICWINDOW_H
#define PROJECT_GENERICWINDOW_H

#include <SDL.h>
#include <SDL_video.h>
#include "../GameAux.h"
#include "Widget.h"
#include <dirent.h>
#include "../XMLLoadParser.h"
#include "../XMLSaveParser.h"

typedef enum {
    WELCOME_WINDOW,
    GAME_WINDOW,
    LOAD_WINDOW,
    SETTINGS_MODE_WINDOW,
    SETTINGS_DIFFICULTY_WINDOW,
    SETTINGS_COLOR_WINDOW
} WINDOW_TYPE;

typedef enum {
    NEW_WINDOW,
    SAME_WINDOW,
    BACK_WINDOW,
    EXIT_WINDOW,
    NO_STATUS
} RESPONSE_STATUS;

typedef struct eventResponse {
    WINDOW_TYPE windowType;
    RESPONSE_STATUS status;
} EVENT_RESPONSE;

typedef struct generic_window {
    SDL_Window *window;
    SDL_Renderer *renderer;
    WIDGET **widgets;
    int numWidgets;
    int overlays;
    WINDOW_TYPE type;
    int savedLastChange;
    EVENT_RESPONSE *(*handleWindowEvent)(struct generic_window *, SDL_Event *event, CHESS_MATCH *match, MOVES_STACK *stack);
} GENERIC_WINDOW;

/**
 * Creates a generic window.
 * This is used to create a new window with a certain draw function.
 * This function performs the retrieved function upon a newly created window struct
 * @param drawFunc
 * @paran SDL_Window
 * @param SDL_Renderer
 * @param CHESS_MATCH
 * @return Ptr to the created generic window
 */

GENERIC_WINDOW *createGenericWindow(int(*drawFunc)(GENERIC_WINDOW* genericWindow, SDL_Window *sdlWindow, SDL_Renderer *renderer, CHESS_MATCH *match),
                                    SDL_Window *, SDL_Renderer *, CHESS_MATCH *);

/**
 * Destroys a certain window
 */
void destroyWindow(GENERIC_WINDOW *);

/**
 * Destroys a window that is not completely created
 * @param window
 * @param numWidgetsCreated
 * @return -1 on destroy
 */
int destroyWindowOnFailure(GENERIC_WINDOW *window, int numWidgetsCreated);

/**
 * Detects a certain widget according to it's <x,y> screen position
 * @param window
 * @param x
 * @param y
 * @return the found widget's index of window->widgets
 */
int detectWidgetByLocation(GENERIC_WINDOW *window, int x, int y);

/**
 * Finds a clicked widget according to the event
 * @param window
 * @param event
 * @return the found widget's index of window->widgets
 */
int getClickedWidget(GENERIC_WINDOW *window, SDL_Event *event);

/**
 * Re-render only the widgets of a certain window
 * @param window
 */
void renderWindowWidgets(GENERIC_WINDOW *window);

/**
 * Re-render the whole window
 * @param window
 */
void reRenderWindow(GENERIC_WINDOW *window);

/**
 * Creates an event response.
 * this is used for decision making in GUI manager
 * @param windowType
 * @param status
 * @return the response created
 */
// Event handler response to GUI Manager
EVENT_RESPONSE *createEventResponse(WINDOW_TYPE windowType, RESPONSE_STATUS status);

/**
 * Destroys a certain response
 */
void destroyEventResponse(EVENT_RESPONSE *);

/**
 * Finds the active button
 * this is used when only 1 button is active in a window
 * @param window
 * @return the button index
 */
int findActiveButton(GENERIC_WINDOW *window);

// utils functions needed by more than 1 window

/**
 * @return the number of saved files in the directory
 */
int getNumSavedFilesInGameDir();

/**
 * Generates a filepath to a certain game
 * @param allocStr
 * @param activeButtonIndex
 */
void generateAddressToChosenGame(char *allocStr, int activeButtonIndex);

/**
 * because of the generic infrastructure of the code a match/stack pointers have to be passed to an event handle function
 * the match/stack object is changed by few windows like the load game and setting and game window
 * therefore in order to avoid "unused argument error" we must use the arguments inside the function
 * @param match
 * @param stack
 * @return unused int
 */
int useMatchAndStack(CHESS_MATCH *match, MOVES_STACK *stack);

#endif //PROJECT_GENERICWINDOW_H


