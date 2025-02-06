#include <iostream>
#include "tetramini.hpp"
#include "smashboy.hpp"

/**
 * Costruttore della classe
 * @param world il mondo in cui esisterà il tetramino
 */
Smashboy::Smashboy(World world): Tetramino(world, 2, 2) {}

/**
 * Strampa il tetraminino nel suo frame attuale
 */
void Smashboy::print_frame() {
	Tetramino::print(frame);
}

/**
 * Muove il tetramino senza farlo strabordare fuori dal mondo
 * @param dir positiva se a destra negativa altrimenti
 */
void Smashboy::safe_move(int dir) {
	int s = side_collisions(dir);

	if(!s && dir > 0 && x < SCRW-WIDTH)
		Tetramino::move(dir);
	if(!s && dir < 0 && x > XOFF+1)
		Tetramino::move(dir);
}

int Smashboy::side_collisions(int side) {
	char c;
	int i, off, result = 0;

	if(side < 0)
		off = x-1;
	else
		off = x + WIDTH;

	for(i=y; i<y+HEIGHT; i++) {
		c = mvinch(i, off) & A_CHARTEXT;
		if(c == '[' || c == ']')
			result++;
	}

	return result!=0;
}
