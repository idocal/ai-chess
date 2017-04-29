//
// Created by okleinfeld on 4/26/2017.
//

#include <stdio.h>

int array_max(int *, int);

int check_num_heaps_validity(int N){
    if (N >=1 && N <= 32){
        return 1;
    }
    else{
        printf("Error: the number of heaps must be between 1 and 32.\n");
        return 0;
    }
}

int array_max(int *array, int n){
    int max = array[0];
    for (int i = 1; i < n; i++){
        if (array[i] > max){
            max = array[i];
        }
    }
    return max;
}

void print_game_board(int * heaps, int N) {
    int max = array_max(heaps, N);
    char board_mat[max][N];
    for (int i = 0; i < max; i++) {
        for (int j = 0; j < N; j++) {
            if (*(heaps + j) > i) {
                board_mat[i][j] = '*';
            } else {
                board_mat[i][j] = ' ';
            }
        }
    }
    for (int i = max - 1; i >= 0; i--) {
        for (int j = 0; j < N; j++) {
            printf("%c", board_mat[i][j]);
            if (j < N - 1) {
                printf("\t");
            }
        }
        printf("\n");
    }
}

void parse_heap_sizes(int *heaps, int n){
    for (int i = 0; i < n; i++){
        scanf("%d", &heaps[i]);
    }
}

int check_heap_size_validity(int *heaps, int n){
    for (int i = 0; i < n; i++){
        if (heaps[i] <= 0){
            printf("Error: the size of heap %d should be positive.\n", i+1);
            return 0;
        }
    }
    return 1;
}

void print_turn_status(int turn, int *heaps, int n) {
    printf("In turn %d heap sizes are:", turn);
    for (int i = 0; i < n; i++) {
        printf(" h%d=%d", i+1, heaps[i]);
    }
    printf(".\n");
}

void parse_user_turn(int *turn) {
    for (int i = 0; i < 2; i++) {
        scanf("%d", &turn[i]);
    }
}

int check_turn_validity(int *heaps, int *turn, int n) {
    int heap_num = turn[0]-1;
    int heap_withdrawal = turn[1];
    if (heaps[heap_num] - heap_withdrawal >= 0
        && heap_withdrawal > 0
        && heap_num < n && heap_num >= 0){
        return 1;
    }
    printf("Error: Invalid input.\nPlease enter again the heap index and the number of removed objects.\n");
    return 0;
}

int play_turn(int *heaps, int *turn, int n) {
    printf("Your turn: please enter the heap index and the number of removed objects.\n");
    parse_user_turn(turn);
    int heap_num = turn[0]-1;
    int heap_withdrawal = turn[1];

    if (check_turn_validity(heaps, turn, n) == 0)  {
        return 0;
    }

    else {
        heaps[heap_num] -= heap_withdrawal;
        return 1;
    }
}