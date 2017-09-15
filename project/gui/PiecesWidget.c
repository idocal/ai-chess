//
// Created by Ido on 9/10/17.
//

#include "PiecesWidget.h"

int setPiecesOnBoard(GENERIC_WINDOW *window, CHESS_MATCH *match) {
    WIDGET **widgets = window->widgets;
    SDL_Renderer *renderer = window->renderer;
    MATRIX *board = match->game->gameBoard;
    int createdWidgets = 0;

    // Create widgets for each cell in the board which is not '_'
    for (int row = 0; row < nRows; row++) {
        for (int col = 0; col < nCols; col++) {
            char piece = matGet(board, row, col);
            if (piece != '_') {
                int x = screenPositionX(col);
                int y = screenPositionY(row);
                widgets[createdWidgets+1] = createPieceGUI(x, y, piece, renderer);
                if (widgets[createdWidgets+1] == NULL) destroyWindowOnFailure(window, createdWidgets);
                createdWidgets++;
            }
        }
    }

    return createdWidgets;
}