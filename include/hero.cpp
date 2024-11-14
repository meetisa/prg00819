#include "hero.hpp"

Hero::Hero(World world): Tetramino(world, 4, 4) {}

void Hero::print_frame() {
	Tetramino::print(frames[current]);
}

void Hero::safe_move(int dir) {
	if(!side_collisions()) {
		int l_limit = (dir<0) * (XOFF - (current * 2) + 1);
		int r_limit = ((dir<0)*SCRW) + XOFF + SCRW + (current * 4) - WIDTH - 1;

		if(x > l_limit && x < r_limit)
			Tetramino::move(dir);
	}
}

void Hero::rotate() {
	werase(base);

	if(++current >= FRLEN)
		current = 0;

	if(x < XOFF)
		move(2);
	if(current==0 && x > XOFF + SCRW - WIDTH*2)
		move(-4);

	print_frame();

	wrefresh(base);
}

int Hero::side_collisions() {
	int coll = 0;
	if(current) {
		for(int i=y; i<y+WIDTH; i++) {
			char c = mvinch(i, x+4) & A_CHARTEXT;
			if(c == '[') {
				coll = 1;
				break;
			}
		}
	}
	else {
		char c = mvinch(y+HEIGHT-1, x+WIDTH) & A_CHARTEXT;
		if(c == '[')
			coll = 1;
	}
	return coll;
}
