#include <stdio.h>
#include "main_aux.h"
#include "sp_nim.h"


int main() {
    //GAME SETUP
    int N;
    int player = 0;
    int turn = 1;
    int turn_decision[2];
    printf("Enter the number of heaps\n");
    scanf("%d", &N);
    if (check_num_heaps_validity(N) == 0){return 0;}
    #define LENGTH N
    printf("Enter the heaps sizes\n");
    int heaps[LENGTH];
    int NS_heaps[LENGTH];
    int winner_heaps[LENGTH];
    parse_heap_sizes(heaps, LENGTH);
    if (check_heap_size_validity(heaps, LENGTH) == 0) { return 0;}

    // GAME LOOP
    while (game_over(heaps, LENGTH, player) == 0) {

        print_turn_status(turn, heaps, LENGTH);
        if (player == 0) { // Computer turn
            computer_decision(turn_decision, NS_heaps, winner_heaps, heaps, LENGTH);
            play_computer_turn(turn_decision, heaps);
        } else { // Player turn
            print_game_board(heaps, LENGTH);
            printf("Your turn: please enter the heap index and the number of removed objects.\n");
            for (int turn_valid = play_turn(heaps, turn_decision, LENGTH); turn_valid == 0;){
                turn_valid = play_turn(heaps, turn_decision, LENGTH);
            }
        }
        player = 1 - player;
        turn++;
    }

    return 0;
}