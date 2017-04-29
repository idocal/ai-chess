//
// Created by okleinfeld on 4/27/2017.
//

#include <stdio.h>



int game_over(int *heaps, int n, int player){
    for (int i = 0; i < n; i++) {
        if (heaps[i] > 0) {
            return 0;
        }
    }
    if (player == 0){
        printf("Computer wins!\n");}
    else{
        printf("You win!\n");}
    return 1;
}
