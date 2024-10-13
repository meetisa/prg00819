#include "hero.hpp"

Hero::Hero(): Tetramino(4, 4) {}

void Hero::print() {
	Tetramino::print(frames[current]);
}
