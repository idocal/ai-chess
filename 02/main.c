#include <stdio.h>
#include "main_aux.h"
#include "sp_nim.h"


int main() {
    int N;
    int player = 0;
    printf("Enter the number of heaps\n");
    scanf("%d", &N);
    if (check_num_heaps_validity(N) == 0){return 0;}
    #define LENGTH N
    printf("Enter the heaps sizes\n");
    int heaps[LENGTH];
    parse_heap_sizes(heaps, LENGTH);
    if (check_heap_size_validity(heaps, LENGTH) == 0) { return 0;}
    print_turn_status(1, heaps, LENGTH);
    print_game_board(heaps, LENGTH);
    int turn[2];
    for (int turn_valid = play_turn(heaps, turn, LENGTH); turn_valid == 0;){
        turn_valid = play_turn(heaps, turn, LENGTH);
    }

    return 0;
}