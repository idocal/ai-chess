//
// Created by okleinfeld on 9/17/17.
//

#ifndef PROJECT_MAINGUI_H
#define PROJECT_MAINGUI_H


#include <stdio.h>
#include "MatchManagement.h"
#include "gui/WelcomeWindow.h"
#include "gui/GuiManager.h"

#define SDL_ERROR_PREFIX "ERROR: unable to init SDL: %s\n"

/**
 * main function to operate the game in GUI mode
 * @return
 */

int mainGui();

#endif //PROJECT_MAINGUI_H
