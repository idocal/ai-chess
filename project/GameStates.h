//
// Created by Ido on 8/19/17.
//

#include "GameRepresenation.h"
#include "PieceRules.h"
#include "stdbool.h"

#ifndef PROJECT_GAMESTATES_H
#define PROJECT_GAMESTATES_H

bool isCheck(CHESS_GAME *game);

bool isCheckMate(CHESS_GAME *game);

bool isTie(CHESS_GAME *game);

void updateGameState(CHESS_GAME *game);

#endif //PROJECT_GAMESTATES_H
