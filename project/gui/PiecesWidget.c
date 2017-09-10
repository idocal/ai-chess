//
// Created by Ido on 9/10/17.
//

#include "PiecesWidget.h"

// Function for each one of the pieces (THIS IS INEVITABLE UNFORTUNATELY!)

// WHITE PIECES:
int createWhiteRook1(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX, initialWhiteY, 'r', renderer, widget);
}

int createWhiteKnight1(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX + PIECE_SIZE, initialWhiteY, 'n', renderer, widget);
}

int createWhiteBishop1(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX + 2 * PIECE_SIZE, initialWhiteY, 'b', renderer, widget);
}

int createWhiteQueen(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX + 3 * PIECE_SIZE, initialWhiteY, 'q', renderer, widget);
}

int createWhiteKing(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX + 4 * PIECE_SIZE, initialWhiteY, 'k', renderer, widget);
}

int createWhiteBishop2(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX + 5 * PIECE_SIZE, initialWhiteY, 'b', renderer, widget);
}

int createWhiteKnight2(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX + 6 * PIECE_SIZE, initialWhiteY, 'n', renderer, widget);
}

int createWhiteRook2(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX + 7 * PIECE_SIZE, initialWhiteY, 'r', renderer, widget);
}

// WHITE PAWNS:

int createWhitePawn1(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX , initialWhiteY - PIECE_SIZE, 'm', renderer, widget);
}

int createWhitePawn2(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX + PIECE_SIZE , initialWhiteY - PIECE_SIZE, 'm', renderer, widget);
}

int createWhitePawn3(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX + 2 * PIECE_SIZE , initialWhiteY - PIECE_SIZE, 'm', renderer, widget);
}

int createWhitePawn4(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX + 3 * PIECE_SIZE , initialWhiteY - PIECE_SIZE, 'm', renderer, widget);
}

int createWhitePawn5(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX + 4 * PIECE_SIZE , initialWhiteY - PIECE_SIZE, 'm', renderer, widget);
}

int createWhitePawn6(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX + 5 * PIECE_SIZE , initialWhiteY - PIECE_SIZE, 'm', renderer, widget);
}

int createWhitePawn7(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX + 6 * PIECE_SIZE , initialWhiteY - PIECE_SIZE, 'm', renderer, widget);
}

int createWhitePawn8(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX + 7 * PIECE_SIZE , initialWhiteY - PIECE_SIZE, 'm', renderer, widget);
}

// BLACK PIECES:
int createBlackRook1(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX, initialBlackY, 'R', renderer, widget);
}

int createBlackKnight1(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX + PIECE_SIZE, initialBlackY, 'N', renderer, widget);
}

int createBlackBishop1(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX + 2 * PIECE_SIZE, initialBlackY, 'B', renderer, widget);
}

int createBlackQueen(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX + 3 * PIECE_SIZE, initialBlackY, 'Q', renderer, widget);
}

int createBlackKing(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX + 4 * PIECE_SIZE, initialBlackY, 'K', renderer, widget);
}

int createBlackBishop2(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX + 5 * PIECE_SIZE, initialBlackY, 'B', renderer, widget);
}

int createBlackKnight2(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX + 6 * PIECE_SIZE, initialBlackY, 'N', renderer, widget);
}

int createBlackRook2(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX + 7 * PIECE_SIZE, initialBlackY, 'R', renderer, widget);
}

// BLACK PAWNS:

int createBlackPawn1(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX , initialBlackY + PIECE_SIZE, 'M', renderer, widget);
}

int createBlackPawn2(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX + PIECE_SIZE , initialBlackY + PIECE_SIZE, 'M', renderer, widget);
}

int createBlackPawn3(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX + 2 * PIECE_SIZE , initialBlackY + PIECE_SIZE, 'M', renderer, widget);
}

int createBlackPawn4(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX + 3 * PIECE_SIZE , initialBlackY + PIECE_SIZE, 'M', renderer, widget);
}

int createBlackPawn5(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX + 4 * PIECE_SIZE , initialBlackY + PIECE_SIZE, 'M', renderer, widget);
}

int createBlackPawn6(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX + 5 * PIECE_SIZE , initialBlackY + PIECE_SIZE, 'M', renderer, widget);
}

int createBlackPawn7(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX + 6 * PIECE_SIZE , initialBlackY + PIECE_SIZE, 'M', renderer, widget);
}

int createBlackPawn8(WIDGET *widget, SDL_Renderer *renderer) {
    return createPieceGUI(initialX + 7 * PIECE_SIZE , initialBlackY + PIECE_SIZE, 'M', renderer, widget);
}

void setPiecesOnBoard(GENERIC_WINDOW *window) {
    WIDGET **widgets = window->widgets;
    SDL_Renderer *renderer = window->renderer;

    // Set white pieces on board
    widgets[1] = createWidget(createWhiteRook1, renderer);
    widgets[2] = createWidget(createWhiteKnight1, renderer);
    widgets[3] = createWidget(createWhiteBishop1, renderer);
    widgets[4] = createWidget(createWhiteQueen, renderer);
    widgets[5] = createWidget(createWhiteKing, renderer);
    widgets[6] = createWidget(createWhiteBishop2, renderer);
    widgets[7] = createWidget(createWhiteKnight2, renderer);
    widgets[8] = createWidget(createWhiteRook2, renderer);

    widgets[9] = createWidget(createWhitePawn1, renderer);
    widgets[10] = createWidget(createWhitePawn2, renderer);
    widgets[11] = createWidget(createWhitePawn3, renderer);
    widgets[12] = createWidget(createWhitePawn4, renderer);
    widgets[13] = createWidget(createWhitePawn5, renderer);
    widgets[14] = createWidget(createWhitePawn6, renderer);
    widgets[15] = createWidget(createWhitePawn7, renderer);
    widgets[16] = createWidget(createWhitePawn8, renderer);

    // Set black piece on board
    widgets[17] = createWidget(createBlackRook1, renderer);
    widgets[18] = createWidget(createBlackKnight1, renderer);
    widgets[19] = createWidget(createBlackBishop1, renderer);
    widgets[20] = createWidget(createBlackQueen, renderer);
    widgets[21] = createWidget(createBlackKing, renderer);
    widgets[22] = createWidget(createBlackBishop2, renderer);
    widgets[23] = createWidget(createBlackKnight2, renderer);
    widgets[24] = createWidget(createBlackRook2, renderer);

    widgets[25] = createWidget(createBlackPawn1, renderer);
    widgets[26] = createWidget(createBlackPawn2, renderer);
    widgets[27] = createWidget(createBlackPawn3, renderer);
    widgets[28] = createWidget(createBlackPawn4, renderer);
    widgets[29] = createWidget(createBlackPawn5, renderer);
    widgets[30] = createWidget(createBlackPawn6, renderer);
    widgets[31] = createWidget(createBlackPawn7, renderer);
    widgets[32] = createWidget(createBlackPawn8, renderer);
}