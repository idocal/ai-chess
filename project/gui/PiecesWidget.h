//
// Created by Ido on 9/10/17.
//

#ifndef PROJECT_PIECESWIDGET_H
#define PROJECT_PIECESWIDGET_H

#include "GenericWindow.h"

// WHITE PIECES:

int createWhiteRook1(WIDGET *widget, SDL_Renderer *renderer);
int createWhiteKnight1(WIDGET *widget, SDL_Renderer *renderer);
int createWhiteBishop1(WIDGET *widget, SDL_Renderer *renderer);
int createWhiteQueen(WIDGET *widget, SDL_Renderer *renderer);
int createWhiteKing(WIDGET *widget, SDL_Renderer *renderer);
int createWhiteBishop2(WIDGET *widget, SDL_Renderer *renderer);
int createWhiteKnight2(WIDGET *widget, SDL_Renderer *renderer);
int createWhiteRook2(WIDGET *widget, SDL_Renderer *renderer);

// WHITE PAWNS:

int createWhitePawn1(WIDGET *widget, SDL_Renderer *renderer);
int createWhitePawn2(WIDGET *widget, SDL_Renderer *renderer);
int createWhitePawn3(WIDGET *widget, SDL_Renderer *renderer);
int createWhitePawn4(WIDGET *widget, SDL_Renderer *renderer);
int createWhitePawn5(WIDGET *widget, SDL_Renderer *renderer);
int createWhitePawn6(WIDGET *widget, SDL_Renderer *renderer);
int createWhitePawn7(WIDGET *widget, SDL_Renderer *renderer);
int createWhitePawn8(WIDGET *widget, SDL_Renderer *renderer);

// BLACK PIECES:

int createBlackRook1(WIDGET *widget, SDL_Renderer *renderer);
int createBlackKnight1(WIDGET *widget, SDL_Renderer *renderer);
int createBlackBishop1(WIDGET *widget, SDL_Renderer *renderer);
int createBlackQueen(WIDGET *widget, SDL_Renderer *renderer);
int createBlackKing(WIDGET *widget, SDL_Renderer *renderer);
int createBlackBishop2(WIDGET *widget, SDL_Renderer *renderer);
int createBlackKnight2(WIDGET *widget, SDL_Renderer *renderer);
int createBlackRook2(WIDGET *widget, SDL_Renderer *renderer);

// BLACK PAWNS:

int createBlackPawn1(WIDGET *widget, SDL_Renderer *renderer);
int createBlackPawn2(WIDGET *widget, SDL_Renderer *renderer);
int createBlackPawn3(WIDGET *widget, SDL_Renderer *renderer);
int createBlackPawn4(WIDGET *widget, SDL_Renderer *renderer);
int createBlackPawn5(WIDGET *widget, SDL_Renderer *renderer);
int createBlackPawn6(WIDGET *widget, SDL_Renderer *renderer);
int createBlackPawn7(WIDGET *widget, SDL_Renderer *renderer);
int createBlackPawn8(WIDGET *widget, SDL_Renderer *renderer);

int setPiecesOnBoard(GENERIC_WINDOW *window, CHESS_MATCH *match);

#endif //PROJECT_PIECESWIDGET_H
