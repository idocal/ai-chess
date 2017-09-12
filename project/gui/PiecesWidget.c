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

int setPiecesOnBoard(GENERIC_WINDOW *window) {
    WIDGET **widgets = window->widgets;
    SDL_Renderer *renderer = window->renderer;
    int createdWidgets = 0;

    // Set white pieces on board
    widgets[1] = createWidget(createWhiteRook1, renderer);
    if (widgets[1] == NULL) return createdWidgets;
    createdWidgets++;

    widgets[2] = createWidget(createWhiteKnight1, renderer);
    if (widgets[2] == NULL) return createdWidgets;
    createdWidgets++;

    widgets[3] = createWidget(createWhiteBishop1, renderer);
    if (widgets[3] == NULL) return createdWidgets;
    createdWidgets++;

    widgets[4] = createWidget(createWhiteQueen, renderer);
    if (widgets[4] == NULL) return createdWidgets;
    createdWidgets++;

    widgets[5] = createWidget(createWhiteKing, renderer);
    if (widgets[5] == NULL) return createdWidgets;
    createdWidgets++;

    widgets[6] = createWidget(createWhiteBishop2, renderer);
    if (widgets[6] == NULL) return createdWidgets;
    createdWidgets++;

    widgets[7] = createWidget(createWhiteKnight2, renderer);
    if (widgets[7] == NULL) return createdWidgets;
    createdWidgets++;

    widgets[8] = createWidget(createWhiteRook2, renderer);
    if (widgets[8] == NULL) return createdWidgets;
    createdWidgets++;

    widgets[9] = createWidget(createWhitePawn1, renderer);
    if (widgets[9] == NULL) return createdWidgets;
    createdWidgets++;

    widgets[10] = createWidget(createWhitePawn2, renderer);
    if (widgets[10] == NULL) return createdWidgets;
    createdWidgets++;

    widgets[11] = createWidget(createWhitePawn3, renderer);
    if (widgets[11] == NULL) return createdWidgets;
    createdWidgets++;

    widgets[12] = createWidget(createWhitePawn4, renderer);
    if (widgets[12] == NULL) return createdWidgets;
    createdWidgets++;

    widgets[13] = createWidget(createWhitePawn5, renderer);
    if (widgets[13] == NULL) return createdWidgets;
    createdWidgets++;

    widgets[14] = createWidget(createWhitePawn6, renderer);
    if (widgets[14] == NULL) return createdWidgets;
    createdWidgets++;

    widgets[15] = createWidget(createWhitePawn7, renderer);
    if (widgets[15] == NULL) return createdWidgets;
    createdWidgets++;

    widgets[16] = createWidget(createWhitePawn8, renderer);
    if (widgets[16] == NULL) return createdWidgets;
    createdWidgets++;

    // Set black piece on board
    widgets[17] = createWidget(createBlackRook1, renderer);
    if (widgets[17] == NULL) return createdWidgets;
    createdWidgets++;

    widgets[18] = createWidget(createBlackKnight1, renderer);
    if (widgets[18] == NULL) return createdWidgets;
    createdWidgets++;

    widgets[19] = createWidget(createBlackBishop1, renderer);
    if (widgets[19] == NULL) return createdWidgets;
    createdWidgets++;

    widgets[20] = createWidget(createBlackQueen, renderer);
    if (widgets[20] == NULL) return createdWidgets;
    createdWidgets++;

    widgets[21] = createWidget(createBlackKing, renderer);
    if (widgets[21] == NULL) return createdWidgets;
    createdWidgets++;

    widgets[22] = createWidget(createBlackBishop2, renderer);
    if (widgets[22] == NULL) return createdWidgets;
    createdWidgets++;

    widgets[23] = createWidget(createBlackKnight2, renderer);
    if (widgets[23] == NULL) return createdWidgets;
    createdWidgets++;

    widgets[24] = createWidget(createBlackRook2, renderer);
    if (widgets[24] == NULL) return createdWidgets;
    createdWidgets++;

    widgets[25] = createWidget(createBlackPawn1, renderer);
    if (widgets[25] == NULL) return createdWidgets;
    createdWidgets++;

    widgets[26] = createWidget(createBlackPawn2, renderer);
    if (widgets[26] == NULL) return createdWidgets;
    createdWidgets++;

    widgets[27] = createWidget(createBlackPawn3, renderer);
    if (widgets[27] == NULL) return createdWidgets;
    createdWidgets++;

    widgets[28] = createWidget(createBlackPawn4, renderer);
    if (widgets[28] == NULL) return createdWidgets;
    createdWidgets++;

    widgets[29] = createWidget(createBlackPawn5, renderer);
    if (widgets[29] == NULL) return createdWidgets;
    createdWidgets++;

    widgets[30] = createWidget(createBlackPawn6, renderer);
    if (widgets[30] == NULL) return createdWidgets;
    createdWidgets++;

    widgets[31] = createWidget(createBlackPawn7, renderer);
    if (widgets[31] == NULL) return createdWidgets;
    createdWidgets++;

    widgets[32] = createWidget(createBlackPawn8, renderer);
    if (widgets[32] == NULL) return createdWidgets;
    createdWidgets++;

    return createdWidgets;
}