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
	if(dir > 0 && x < SCRW-WIDTH)
		Tetramino::move(dir);
	if(dir < 0 && x > XOFF+1)
		Tetramino::move(dir);
}
