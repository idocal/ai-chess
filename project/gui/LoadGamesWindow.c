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
    genericWindow->type = SETTINGS_MODE_WINDOW;
    genericWindow->handleWindowEvent = (void *) loadGameEventHandler;

    // Assign application's window and renderer
    genericWindow->window = sdlWindow;
    genericWindow->renderer = renderer;


    WIDGET **widgets = (WIDGET **) calloc(numWidgets, sizeof(WIDGET *));
    if (widgets == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
    genericWindow->widgets = widgets;

    // Load widgets into widgets array
    // back and load buttons always exist. we'll denote them widget 0 and 1 respectively
    widgets[0] = createWidget(createBackButton, renderer);
    if (widgets[0] == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
    numWidgetsCreated++;

    widgets[1] = createWidget(createLoadGameButton, renderer);
    if (widgets[1] == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
    numWidgetsCreated++;

    //now load saved files widgets depending on number of files
    for (int i = 0; i < numFiles; ++i){
        int widgetIndex = i+2;
        int slotNum = i+1;
        widgets[widgetIndex] = createGameSlotWidget(createGameSlotButton, renderer, slotNum);
        if (widgets[widgetIndex] == NULL) return destroyWindowOnFailure(genericWindow, numWidgetsCreated); // On failure
        numWidgetsCreated++;
    }

    reRenderWindow(genericWindow);
    return 1;
}






int createLoadGameButton(WIDGET *widget, SDL_Renderer *renderer) {
    int x = (WINDOW_WIDTH - (2 * BUTTON_WIDTH + BUTTON_MARGIN)) / 2 + BUTTON_WIDTH + BUTTON_MARGIN;
    int y = WINDOW_HEIGHT - PAGE_MARGIN - BUTTON_HEIGHT;
    return createButton(x, y, "./img/load.bmp", renderer, widget, false);
}


int createGameSlotButton(WIDGET *widget, SDL_Renderer *renderer, int slotNum) {
    char imgPath[100];
    getGameSlotButtonPath(imgPath, slotNum);
    int yPosition = getGameSlotButtonYposition(slotNum);
    return createButton(WINDOW_MIDDLE_X_POS, yPosition, imgPath, renderer, widget, false);
}


int getNumSavedFilesInGameDir(){
    struct dirent *dirEntry; // Pointer to the directory entry
    DIR *directory = opendir("saved_games"); // Pointer to a directory object
    if (directory == NULL){
        return -1;
    }
    int filesCounter = 0;
    while ((dirEntry = readdir(directory)) != NULL){ // more files in the directory
        filesCounter++;
    }
    closedir(directory);
    filesCounter -= 2; // a subdirectory is also an entry so the functions counts also "./" and '../" as entries
    return filesCounter;
}

void getGameSlotButtonPath(char *allocStr, int slotNum){
    char *initPtr = allocStr;
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
