#include "hero.hpp"

Hero::Hero(): Tetramino(4, 4) {}

void Hero::print() {
	Tetramino::print(frames[current]);
}

void Hero::rotate() {
	werase(base);
	wrefresh(base);

	if(++current >= FRLEN)
		current = 0;

	print();
}
