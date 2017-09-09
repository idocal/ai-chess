#include <stdio.h>
#include "MatchManagement.h"
#include "GameAux.h"
#include "gui/WelcomeWindow.h"
#include "gui/GenericWindow.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    createGenericWindow(drawWelcomeWindow);
}


