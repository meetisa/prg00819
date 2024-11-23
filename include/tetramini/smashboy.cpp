#include <iostream>
#include "tetramini.hpp"
#include "smashboy.hpp"

Smashboy::Smashboy(World world): Tetramino(world, 2, 2) {}

void Smashboy::print_frame() {
	Tetramino::print(frame);
}

void Smashboy::safe_move(int dir) {
	if(dir > 0 && x < SCRW-WIDTH)
		Tetramino::move(dir);
	if(dir < 0 && x > XOFF+1)
		Tetramino::move(dir);
}
