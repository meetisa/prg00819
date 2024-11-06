#include <iostream>
#include "tetramini.hpp"
#include "smashboy.hpp"

Smashboy::Smashboy(World world): Tetramino(world, 2, 2) {}

void Smashboy::print() {
	Tetramino::print(frame);
}
