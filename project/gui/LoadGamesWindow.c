//
// Created by okleinfeld on 9/11/17.
//

#include "LoadGamesWindow.h"

int drawLoadGameWindow(GENERIC_WINDOW *genericWindow, SDL_Window *sdlWindow, SDL_Renderer *renderer, CHESS_MATCH *match) {
    int numFiles = getNumSavedFilesInGameDir();
    if (numFiles == -1){
        return -1;
    }
    int numWidgets = numFiles + 2; // extra back and load buttons
    genericWindow->numWidgets = numWidgets;
    int numWidgetsCreated = 0;
    genericWindow->type = LOAD_WINDOW;
    genericWindow->handleWindowEvent = (void *) loadGameWindowEventHandler;

    // Assign application's window and renderer
    genericWindow->window = sdlWindow;
    genericWindow->renderer = renderer;


    WIDGET **widgets = (WIDGET **) calloc(numWidgets, sizeof(WIDGET *));
    if (widgets == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
    genericWindow->widgets = widgets;

    // Load widgets into widgets array
    // back and load buttons always exist.
    // we'll denote back button as widget[0] and load button as widget[numWidgets-1]
    widgets[0] = createWidget(createBackButton, renderer);
    if (widgets[0] == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
    numWidgetsCreated++;

    widgets[numWidgets-1] = createWidget(createDisabledLoadGameButton, renderer);
    if (widgets[numWidgets-1] == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
    numWidgetsCreated++;

    //now load saved files widgets depending on number of files
    for (int i = 1; i < numFiles+1; ++i){
        int widgetIndex = i;
        int slotNum = i;
        widgets[widgetIndex] = createGameSlotWidget(createGameSlotButton, renderer, slotNum);
        if (widgets[widgetIndex] == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
        numWidgetsCreated++;
    }

    reRenderWindow(genericWindow);
    return 1;
}


EVENT_RESPONSE *loadGameWindowEventHandler(GENERIC_WINDOW *window, SDL_Event *event, CHESS_MATCH *match, MOVES_STACK *stack){
    WINDOW_TYPE nextWindow = LOAD_WINDOW;
    int widgetIndex = getClickedWidget(window, event);
    WIDGET *clickedWidget = window->widgets[widgetIndex];
    WIDGET *loadGameWidget = window->widgets[window->numWidgets -1];
    EVENT_RESPONSE *response = createEventResponse(nextWindow, SAME_WINDOW);

    if (widgetIndex == 0) { // The button clicked is back button
        response->status = BACK_WINDOW;
    } else if (widgetIndex == window->numWidgets -1){ // load game button is clicked

        if (clickedWidget->isEnable){ // only load game if load game is enabled

            int activeButton = findActiveButton(window); // find which game to load
            char pathToGame[100];
            generateAddressToChosenGame(pathToGame, activeButton);
            CHESS_MATCH *loadedMatch = parseXMLGameFile(pathToGame);
            if (loadedMatch == NULL) { // an allocation error occurred cannot load game
                return response;
            }
            // we must copy loaded match content because we cannot change where our game's match object points to
            // we only have to address where match points to (by value)
            deepCopyFromLoadedMatch(match, loadedMatch);
            destroyChessMatch(loadedMatch);

            response->windowType = GAME_WINDOW;
            response->status = NEW_WINDOW;
        }

    } else if (widgetIndex >= 1 && widgetIndex < window->numWidgets - 1){

        if (!clickedWidget->isActive) { // user want to choose a button / activate it
            int activeButton = findActiveButton(window);

            if (activeButton != -1){ // if there is already an active button must deactivate it
                toggleButton(window->widgets[activeButton], window->renderer);
            }

            toggleButton(clickedWidget, window->renderer); // anyway activate the selected button

            if (!loadGameWidget->isEnable) // and activate the load game button if it is not enabled yet
            toggleButtonAbility(loadGameWidget, window->renderer);

        } else { // user is deactivating an active button
            toggleButton(clickedWidget, window->renderer); // make button inactive
            toggleButtonAbility(loadGameWidget, window->renderer); // make load game option disabled
        }
        reRenderWindow(window); // anyway has to reRender window
    }

    return response;

}



int createDisabledLoadGameButton(WIDGET *widget, SDL_Renderer *renderer) {
    int x = (WINDOW_WIDTH - (2 * BUTTON_WIDTH + BUTTON_MARGIN)) / 2 + BUTTON_WIDTH + BUTTON_MARGIN;
    int y = WINDOW_HEIGHT - PAGE_MARGIN - BUTTON_HEIGHT;
    return createDisabledButton(x, y, "./img/load_disabled.bmp", renderer, widget, false);
}


int createGameSlotButton(WIDGET *widget, SDL_Renderer *renderer, int slotNum) {
    char imgPath[100];
    getGameSlotButtonPath(imgPath, slotNum);
    int yPosition = getGameSlotButtonYposition(slotNum);
    return createButton(WINDOW_MIDDLE_X_POS, yPosition, imgPath, renderer, widget, false);
}




void getGameSlotButtonPath(char *allocStr, int slotNum){
    char slotNumChar = slotNum + '0';
    strcpy(allocStr, "./img/slot");
    while (*allocStr != '\0'){
        allocStr++;
    }
    *allocStr = slotNumChar;
    allocStr++;
    *allocStr = '\0';
    strcat(allocStr, ".bmp");
}

int getGameSlotButtonYposition(int slotNum){
    int reducedMargin = 15;
    if (slotNum == 1){
        return reducedMargin; // REDUCED PAGE MARGIN
    } else if (slotNum == 2){
        return reducedMargin + 100 + 15; // REDUCED PAGE MARGIN + BUTTON HEIGHT + PAGE MARGIN
    } else if (slotNum == 3){
        return reducedMargin + 2*100 + 2*15; // REDUCED PAGE MARGIN + 2 * BUTTON HEIGHT + 2 * PAGE MARGIN
    } else if (slotNum == 4){
        return reducedMargin + 3*100 + 3*15; // REDUCED PAGE MARGIN + 3 * BUTTON HEIGHT + 3 * PAGE MARGIN
    } else if (slotNum == 5){
        return reducedMargin + 4*100 + 4*15; // REDUCED PAGE MARGIN + 4 * BUTTON HEIGHT + 4 * PAGE MARGIN
    } else { // not intend to happen
        return -1;
    }
}



void deepCopyFromLoadedMatch(CHESS_MATCH *existingMatch, CHESS_MATCH *loadedMatch){
    existingMatch->gameMode = loadedMatch->gameMode;
    existingMatch->level = loadedMatch->level;
    existingMatch->userColor = loadedMatch->userColor;

    existingMatch->game->status = loadedMatch->game->status;
    existingMatch->game->currentPlayer = loadedMatch->game->currentPlayer;
    existingMatch->game->pruningThreshold = loadedMatch->game->pruningThreshold;

    existingMatch->game->gameBoard->rows = loadedMatch->game->gameBoard->rows;
    existingMatch->game->gameBoard->cols = loadedMatch->game->gameBoard->cols;

    int rows = existingMatch->game->gameBoard->rows;
    int cols = existingMatch->game->gameBoard->cols;
    for (int i = 0; i < rows * cols; ++i){
        existingMatch->game->gameBoard->p[i] = loadedMatch->game->gameBoard->p[i];
    }
}