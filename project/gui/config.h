//
// Created by Ido on 9/11/17.
//

#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define NARROW_WINDOW_WIDTH 550
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

#define SAVE_FILEPATH "game_saved.xml"

#endif //PROJECT_CONFIG_H
