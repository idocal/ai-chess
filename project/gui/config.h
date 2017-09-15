//
// Created by Ido on 9/11/17.
//

#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define COLOR_WHITE 255, 255, 255, 1

#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 100
#define BUTTON_MARGIN 15
#define PAGE_MARGIN 64
#define TITLE_WIDTH 530
#define TITLE_HEIGHT 40

#define BOARD_WIDTH 640
#define BOARD_HEIGHT 640
#define PIECE_SIZE 80
#define initialX (WINDOW_WIDTH - BUTTON_MARGIN - BOARD_WIDTH)
#define initialBlackY PAGE_MARGIN
#define initialWhiteY (PAGE_MARGIN + BOARD_WIDTH - PIECE_SIZE)
#define screenPositionX(col) (initialX + 80 * col)
#define screenPositionY(row) (initialBlackY + 80 * (7 - row))

#define SAVE_FILE_PATH "./saved_games/game_slot1.xml"
#define MAXIMUM_NUMBER_OF_SAVED_GAMES_SLOTS 5
#define SAVE_ERROR_TITLE "some unxpected error occurred"
#define SAVE_GAME_ERROR_MESSAGE "your current game wasn't saved and it might be that some of your saved games were damaged"
#define SAVE_SUCCESSFUL_TITLE "game saved successfully"
#define SAVE_GAME_BODY_MESSAGE "your current game was saved to game slot number 1"

#define MOVE_REGULAR 0
#define MOVE_CAPTURE 1
#define MOVE_THREAT 2
#define MOVE_CAPTURE_THREAT 3


#endif //PROJECT_CONFIG_H
