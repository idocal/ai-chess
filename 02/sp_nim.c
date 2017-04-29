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
    if (player == 1){
        printf("Computer wins!\n");}
    else{
        printf("You win!\n");}
    return 1;
}

int compute_NimSum(int *heaps, int n){
    int NimSum = heaps[0];
    for (int i = 1; i < n; i++){
        NimSum ^= heaps[i];
    }
    return NimSum;
}

void compute_heap_NimSum_winner(int *NS_heaps, int *winner_heaps, int *heaps, int n, int NimSum) {
    for (int i = 0; i < n; i++){
        NS_heaps[i] = heaps[i] ^ NimSum;
        if (NS_heaps[i] < heaps[i]){
            winner_heaps[i] = 1;
        }
        else{
            winner_heaps[i] = 0;
        }
    }
}

void computer_decision(int *computer_turn, int *NS_heaps, int *winner_heaps,  int *heaps, int n) {
    int NimSum = compute_NimSum(heaps, n);
    compute_heap_NimSum_winner(NS_heaps, winner_heaps, heaps, n, NimSum);
    if (NimSum != 0) {
        for (int i = 0; i < n; i++) {
            if (winner_heaps[i] == 1) {
                computer_turn[0] = i;
                computer_turn[1] = heaps[i] - NS_heaps[i];
                break;
            }
        }
    } else{
        for (int i = 0; i < n; i++){
            if (heaps[i] > 0){
                computer_turn[0] = i;
                computer_turn[1] = 1;
                break;
            }
        }
    }
}

void play_computer_turn(int *computer_turn, int * heaps) {
    int heap_num = computer_turn[0];
    int withdrawal = computer_turn[1];
    heaps[heap_num] -= withdrawal;
    printf("Computer takes %d objects from heap %d.\n", withdrawal, heap_num+1);
}