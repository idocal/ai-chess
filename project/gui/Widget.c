//
// Created by Ido on 9/9/17.
//

#include "Widget.h"

int loadTexture(WIDGET *widget, char *originalImgPath, SDL_Renderer *renderer);

BOARD_POSITION *createBoardPosition(int row, int col) {
    BOARD_POSITION *position = (BOARD_POSITION *) malloc(sizeof(BOARD_POSITION));
    position->row = row;
    position->col = col;
    return position;
}

WIDGET *createWidget(int(*createWidgetFunc)(WIDGET *, SDL_Renderer *), SDL_Renderer *renderer) {
    WIDGET *widget = (WIDGET *) calloc(sizeof(WIDGET), sizeof(char));
    if (widget == NULL) return NULL;

    widget->isActive = false;
    widget->isEnable = true;
    widget->piece = -1;
    widget->color = -1;
    widget->position = NULL;
    widget->isClickable = true;

    int res = (*createWidgetFunc)(widget, renderer);
    if (res == -1) return NULL;
    return widget;
}

WIDGET *createGameSlotWidget(int(*createWidgetFunc)(WIDGET *, SDL_Renderer *, int), SDL_Renderer *renderer, int slotNum) {
    WIDGET *widget = (WIDGET *) calloc(sizeof(WIDGET), sizeof(char));
    if (widget == NULL) return NULL;

    widget->isActive = false;
    widget->isEnable = true;
    widget->piece = -1;
    widget->color = -1;
    widget->position = NULL;
    widget->isClickable = true;

    int res = (*createWidgetFunc)(widget, renderer, slotNum);
    if (res == -1) return NULL;
    return widget;
}

void destroyWidget(WIDGET *widget) {
    if (widget == NULL) return;
    if (widget->position != NULL) free(widget->position);
    SDL_DestroyTexture(widget->texture);
    free(widget);
}

int createButton(int x, int y, char *imgPath, SDL_Renderer *renderer, WIDGET *widget, bool isActive) {
    strcpy(widget->imgPath, imgPath);

    // WIDGET rect
    SDL_Rect rect = {.x = x, .y = y, .w = BUTTON_WIDTH, .h = BUTTON_HEIGHT};
    widget->rect = rect;
    widget->isActive = isActive;

    // Load new texture with imgPath updated
    loadTexture(widget, widget->imgPath, renderer);

    return 1;
}

int createDisabledButton(int x, int y, char *imgPath, SDL_Renderer *renderer, WIDGET *widget, bool isActive) {
    strcpy(widget->imgPath, imgPath);

    // WIDGET rect
    SDL_Rect rect = {.x = x, .y = y, .w = BUTTON_WIDTH, .h = BUTTON_HEIGHT};
    widget->rect = rect;
    widget->isActive = isActive;
    widget->isEnable = false;

    // Load new texture with imgPath updated
    loadTexture(widget, widget->imgPath, renderer);

    return 1;
}

int createTitle(char *imgPath, SDL_Renderer *renderer, WIDGET *widget) {
    strcpy(widget->imgPath, imgPath);

    // WIDGET rect
    SDL_Rect rect = {.x = (WINDOW_WIDTH - TITLE_WIDTH) / 2, .y = PAGE_MARGIN, .w = TITLE_WIDTH, .h = TITLE_HEIGHT};
    widget->rect = rect;
    widget->isActive = false;

    // Load new texture with imgPath updated
    loadTexture(widget, widget->imgPath, renderer);

    return 1;
}

int createBackground(int x, int y, int w, int h, char *imgPath, SDL_Renderer *renderer, WIDGET *widget) {
    strcpy(widget->imgPath, imgPath);

    // WIDGET rect
    SDL_Rect rect = {.x = x, .y = y, .w = w, .h = h};
    widget->rect = rect;
    widget->isActive = false;
    widget->isClickable = false;

    // Load new texture with imgPath updated
    loadTexture(widget, widget->imgPath, renderer);

    return 1;
}

WIDGET *createMoveCell(int x, int y, SDL_Renderer *renderer, char moveType) {
    WIDGET *widget = (WIDGET *) calloc(sizeof(WIDGET), sizeof(char));
    if (widget == NULL) return NULL;

    widget->isActive = true;
    widget->isEnable = true;
    widget->position = NULL;
    widget->isClickable = true;
    char imgPath[1024];

    switch (moveType) {
        case MOVE_REGULAR :
            strcpy(imgPath, "./img/move_regular.bmp");
            break;
        case MOVE_CAPTURE :
            strcpy(imgPath, "./img/move_capture.bmp");
            break;
        case MOVE_THREAT :
            strcpy(imgPath, "./img/move_threat.bmp");
            break;
        case MOVE_CAPTURE_THREAT :
            strcpy(imgPath, "./img/move_capture_threat.bmp");
            break;
        default :
            break;
    }

    strcpy(widget->imgPath, imgPath);

    // WIDGET rect
    SDL_Rect rect = {.x = x, .y = y, .w = 80, .h = 80};
    widget->rect = rect;
    widget->isActive = false;

    widget->position = calculateBoardPosition(x, y); // Calculate board position according to <x,y>

    // Load new texture with imgPath updated
    loadTexture(widget, widget->imgPath, renderer);

    return widget;
}

WIDGET *createPieceGUI(int x, int y, char piece, SDL_Renderer *renderer) {

    WIDGET *widget = (WIDGET *) calloc(sizeof(WIDGET), sizeof(char));
    if (widget == NULL) return NULL;

    widget->isActive = true;
    widget->isEnable = true;
    widget->position = NULL;
    widget->isClickable = true;
    char imgPath[1024];

    switch (piece) {
        case 'm' :
            strcpy(imgPath, "./img/pawn_white.bmp");
            break;
        case 'M' :
            strcpy(imgPath, "./img/pawn_black.bmp");
            break;
        case 'r' :
            strcpy(imgPath, "./img/rook_white.bmp");
            break;
        case 'R' :
            strcpy(imgPath, "./img/rook_black.bmp");
            break;
        case 'n' :
            strcpy(imgPath, "./img/knight_white.bmp");
            break;
        case 'N' :
            strcpy(imgPath, "./img/knight_black.bmp");
            break;
        case 'b' :
            strcpy(imgPath, "./img/bishop_white.bmp");
            break;
        case 'B' :
            strcpy(imgPath, "./img/bishop_black.bmp");
            break;
        case 'q' :
            strcpy(imgPath, "./img/queen_white.bmp");
            break;
        case 'Q' :
            strcpy(imgPath, "./img/queen_black.bmp");
            break;
        case 'k' :
            strcpy(imgPath, "./img/king_white.bmp");
            break;
        case 'K' :
            strcpy(imgPath, "./img/king_black.bmp");
            break;
        default :
            break;
    }

    strcpy(widget->imgPath, imgPath);

    // WIDGET rect
    SDL_Rect rect = {.x = x, .y = y, .w = 80, .h = 80};
    widget->rect = rect;
    widget->isActive = false;
    widget->piece = piece;

    // Widget characteristics
    if (piece >= 'a' && piece <= 'z') widget->color = 1;
    else if (piece >= 'A' && piece <= 'Z') widget->color = 0;
    widget->position = calculateBoardPosition(x, y); // Calculate board position according to <x,y>

    // Load new texture with imgPath updated
    loadTexture(widget, widget->imgPath, renderer);

    return widget;
}

void toggleButton(WIDGET *widget, SDL_Renderer *renderer) {
    // Save previous img path to restore in case of failure
    char originalImgPath[1024];
    strcpy(originalImgPath,widget->imgPath);

    if (!widget->isActive) {
        // Change image path to _on.bmp
        char *imgPath = widget->imgPath;
        imgPath += 2; // incrementing pointer by two to avoid previous folder prefix
        while (*imgPath != '.') {
            imgPath++;
        }
        *imgPath = '\0';
        char *imgNewSuffix = "_on.bmp";
        strcat(widget->imgPath, imgNewSuffix);
    }

    else { // Widget is inactive
        // Change image path to .bmp
        char *imgPath = widget->imgPath;
        imgPath += 2; // incrementing pointer by two to avoid previous folder prefix
        while (*imgPath != '.') {
            imgPath++;
        }
        imgPath -= 3; // go backwards 3 chars to substitute the "_on" suffix
        *imgPath = '\0';
        char *imgNewSuffix = ".bmp";
        strcat(widget->imgPath, imgNewSuffix);
    }

    // Load new texture with imgPath updated
    loadTexture(widget, originalImgPath, renderer);

    // Widget is now active
    widget->isActive = !widget->isActive;
}

void toggleButtonAbility(WIDGET *widget, SDL_Renderer *renderer) {
    // Save previous img path to restore in case of failure
    char originalImgPath[1024];
    strcpy(originalImgPath,widget->imgPath);

    if (widget->isEnable) {
        // Change image path to _disabled.bmp
        char *imgPath = widget->imgPath;
        imgPath += 2; // incrementing pointer by two to avoid previous folder prefix
        while (*imgPath != '.') {
            imgPath++;
        }
        *imgPath = '\0';
        char *imgNewSuffix = "_disabled.bmp";
        strcat(widget->imgPath, imgNewSuffix);
    }
    else { // Widget is disabled
        // Change image path to .bmp
        char *imgPath = widget->imgPath;
        imgPath += 2; // incrementing pointer by two to avoid previous folder prefix
        while (*imgPath != '.') {
            imgPath++;
        }
        imgPath -= 9; // go backwards 9 chars to substitute the "_on" suffix
        *imgPath = '\0';
        char *imgNewSuffix = ".bmp";
        strcat(widget->imgPath, imgNewSuffix);
    }

    // Load new texture with imgPath updated
    loadTexture(widget, originalImgPath, renderer);

    // Widget is now disabled
    widget->isEnable = !widget->isEnable;
}

int loadTexture(WIDGET *widget, char *originalImgPath, SDL_Renderer *renderer) {
    // Reload texture
    SDL_Surface *loadingSurface = SDL_LoadBMP(widget->imgPath);
    if (loadingSurface == NULL) {
        strcpy(widget->imgPath, originalImgPath); // revert to previous img path
        return -1;
    }

    // Make white transparent
    SDL_SetColorKey(loadingSurface, SDL_TRUE,
                    SDL_MapRGB(loadingSurface->format, 255, 255, 255));

    // Widget texture
    SDL_Texture *prevTexture = widget->texture;
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
    if (texture == NULL) {
        SDL_FreeSurface(loadingSurface);
        strcpy(widget->imgPath, originalImgPath); // revert to previous img path
        return -1;
    }

    widget->texture = texture;
    SDL_DestroyTexture(prevTexture); // Destroy previous texture
    SDL_FreeSurface(loadingSurface);
}

// Common buttons

int createBackButton(WIDGET *widget, SDL_Renderer *renderer) {
    int x = (WINDOW_WIDTH - (2 * BUTTON_WIDTH + BUTTON_MARGIN)) / 2;
    int y = WINDOW_HEIGHT - PAGE_MARGIN - BUTTON_HEIGHT;
    return createButton(x, y, "./img/back.bmp", renderer, widget, false);
}

int createStartButton(WIDGET *widget, SDL_Renderer *renderer) {
    int x = (WINDOW_WIDTH - (2 * BUTTON_WIDTH + BUTTON_MARGIN)) / 2 + BUTTON_WIDTH + BUTTON_MARGIN;
    int y = WINDOW_HEIGHT - PAGE_MARGIN - BUTTON_HEIGHT;
    return createButton(x, y, "./img/start.bmp", renderer, widget, false);
}

int createNextButton(WIDGET *widget, SDL_Renderer *renderer) {
    int x = (WINDOW_WIDTH - (2 * BUTTON_WIDTH + BUTTON_MARGIN)) / 2 + BUTTON_WIDTH + BUTTON_MARGIN;
    int y = WINDOW_HEIGHT - PAGE_MARGIN - BUTTON_HEIGHT;
    return createButton(x, y, "./img/next.bmp", renderer, widget, false);
}

BOARD_POSITION *calculateBoardPosition(int x, int y) {
    int row = 7 - ((y - initialBlackY) / 80);
    int col = (x - initialX) / 80;
    BOARD_POSITION *position = createBoardPosition(row, col);
    return position;
}