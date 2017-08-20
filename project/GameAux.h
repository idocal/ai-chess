//
// Created by Ido on 8/13/17.
//

#ifndef PROJECT_GAMEAUX_H
#define PROJECT_GAMEAUX_H

#include "MatchManagement.h"
#include "CommandParsing.h"
#include <stdbool.h>

/**
 * Performs the move on the actual game board.
 * This function changes the game->gameBoard matrix,
 * so in some cases it is necessary to provide with a copy
 * this can be achieved via copy copyChessGame function.
 *
 * @param game
 * @param move
 */
void performMove(CHESS_GAME *game, GAME_MOVE *move);

/**
 * This function evaluates the SETTING_COMMAND that has been
 * received from the user.
 * The returned int is an indicator for the match settings state loop.
 * Here the setting state messages are also being taken care of.
 *
 * @param match pointer
 * @param cmd
 * @return 1 if game should start,
 * 2 if match should be terminated
 * 0 otherwise
 */
int evaluateSettingStateCommand(CHESS_MATCH **match, SETTING_STATE_COMMAND *cmd);

/**
 * Loops through the user input value until start/quit is received.
 * "start" quits the loop and returns true, "quit" quits the loop and returns false.
 *
 * @param match pointer
 * @return true iff game should start (i.e. status == 1)
 */
bool initiateChessMatch(CHESS_MATCH **match);

/**
 * Loops through the user moves during game state.
 *
 * @param match
 */
void initiateChessGame(CHESS_MATCH *match);

#endif //PROJECT_GAMEAUX_H
