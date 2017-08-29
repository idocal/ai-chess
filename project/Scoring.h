//
// Created by Ido on 8/25/17.
//

#ifndef PROJECT_SCORING_H
#define PROJECT_SCORING_H

#include "PieceRules.h"

#define opponent(player) ((char) (1 - player))

int score(CHESS_GAME *game);
int expertScore(CHESS_GAME *game);

#endif //PROJECT_SCORING_H
