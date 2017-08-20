#include <stdio.h>
#include "MatchManagement.h"
#include "GameAux.h"


#define WELCOME_MESSAGE "Specify game setting or type 'start' to begin a game with the current setting:\n"

int main() {
    bool live = true;
    while (live) {
        printf(WELCOME_MESSAGE);
        CHESS_MATCH *match = createNewChessMatch();
        if (match == NULL){
            return 0;
        }

        // Match settings state loop
        bool initGame = initiateChessMatch(&match);
        if (initGame == false){
            destroyChessMatch(match);
            return 0; // quit program
        }

        // Game state
        live = initiateChessGame(match); // quit program if false
    }
}


