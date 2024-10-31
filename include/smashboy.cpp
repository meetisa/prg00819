#include <iostream>
#include "tetramini.hpp"
#include "smashboy.hpp"

Smashboy::Smashboy(): Tetramino(2, 2) {}

void Smashboy::print() {
	Tetramino::print(frame);
}
