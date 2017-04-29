//
// Created by okleinfeld on 4/27/2017.
//

#ifndef NIMGAME_SP_NIM_H
#define NIMGAME_SP_NIM_H

int game_over(int *, int n, int player);
void play_computer_turn(int *computer_turn, int * heaps);
void computer_decision(int *computer_turn, int *NS_heaps, int *winner_heaps, int *heaps, int n);

#endif //NIMGAME_SP_NIM_H
