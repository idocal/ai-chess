//
// Created by Ido on 8/13/17.
//

#ifndef PROJECT_GAMEAUX_H
#define PROJECT_GAMEAUX_H

#include "MatchManagement.h"
#include "MovesStack.h"
#include "CommandParsing.h"
#include "PieceRules.h"
#include "GameStates.h"
#include "XMLLoadParser.h"
#include "XMLSaveParser.h"
#include "MinMaxTree.h"
#include <stdbool.h>
#include <string.h>

#define UNDO_CAPACITY 6
#define PIECE_NAME_SIZE 512


// General messages
#define FATAL_ERROR_MESSAGE "A fatal error occurred."

// Match settings state messages
#define INVALID_COMMAND_ERROR "Invalid command. Please try again\n"
#define SET_ONE_PLAYER_COMMAND "Game mode is set to 1 player\n"
#define SET_TWO_PLAYERS_COMMAND "Game mode is set to 2 players\n"
#define WRONG_GAME_MODE_COMMAND "Wrong game mode\n"
#define WRONG_DIFFICULTY_LEVEL_ERROR "Wrong difficulty level. the value should be between 1 to 5\n"
#define LOAD_FILE_ERROR "Error: File doesn't exist or cannot be opened\n"
#define EXIT_MESSAGE "Exiting...\n"

// Game state messages
#define NEXT_MOVE_MESSAGE "player - enter your move:\n"
#define INVALID_POSITION_MESSAGE "Invalid position on the board\n"
#define NO_PLAYER_PIECE_LOCATION_MESSAGE "The specified position does not contain your piece\n"
#define ILLEGAL_MOVE_MESSAGE "Illegal move\n"
#define UNDO_UNAVAILABLE_MESSAGE "Undo command not available in 2 players mode\n"
#define EMPTY_HISTORY_MESSAGE "Empty history, move cannot be undone\n"
#define RESTARTING_MESSAGE "Restarting...\n"
#define CHECKMATE_MESSAGE "Checkmate! %s player wins the game\n"
#define TIE_MESSAGE "The game is tied\n"
#define CHECK_MESSAGE "Check: %s King is threatened!\n"
#define CHECK_AI_MESSAGE "Check!\n"
#define COMPUTER_MOVE_MESSAGE "Computer: move %s at <%c,%c> to <%c,%c>\n"

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
 * @param mode (1 or 2)
 * @return true iff resetting (this means program is still live)
 */
bool initiateChessGame(CHESS_MATCH *match);

/**
 * Print all possible moves for a specific piece
 * Add "Threatened" and "Captured" marks if the game level applies so
 *
 * @param sourceRow
 * @param sourceCol
 * @param game
 */
void handleGetMovesCommand(int sourceRow, int sourceCol, CHESS_GAME *game);

#endif //PROJECT_GAMEAUX_H
