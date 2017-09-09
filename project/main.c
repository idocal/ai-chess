#include <stdio.h>
#include "MatchManagement.h"
#include "GameAux.h"
#include "gui/WelcomeWindow.h"
#include "gui/GenericWindow.h"
#include "gui/GuiManager.h"

#define SDL_ERROR_PREFIX "ERROR: unable to init SDL: %s\n"

int main() {
    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf(SDL_ERROR_PREFIX, SDL_GetError());
        return 1;
    };

    // Create GUI manager
    GUI_MANAGER *manager = createManager();
    if (manager == NULL) {
        SDL_Quit();
        return 0;
    }

    // Wait for events in a loop and deal with manager handler
    SDL_Event event;
    while (1) {
        SDL_WaitEvent(&event);
        if (managerEventHandler(manager, &event) == MANAGER_QUIT) break;
    }

    // GUI quit
    destroyManager(manager);
    SDL_Quit();
    return 0;
}


