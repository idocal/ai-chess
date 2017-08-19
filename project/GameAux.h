//
// Created by Ido on 8/13/17.
//

#ifndef PROJECT_GAMEAUX_H
#define PROJECT_GAMEAUX_H

#include "MatchManagement.h"
#include "CommandParsing.h"
#include <stdbool.h>

void performMove(CHESS_GAME *game, GAME_MOVE *move);

int evaluateSettingStateCommand(CHESS_MATCH **match, SETTING_STATE_COMMAND *cmd);

bool initiateChessGame(CHESS_MATCH *match);



#endif //PROJECT_GAMEAUX_H
