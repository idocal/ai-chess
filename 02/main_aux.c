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
        if (i > 0){
            printf("\n");
        }
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
