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
    while (game_over(heaps, LENGTH, player) == 0){
        for (int i = 0; i < LENGTH; i++){
            printf("heap number %d has %d cards\n", i+1, heaps[i]);
            heaps[i]--;
        }
    }
    return 0;
}