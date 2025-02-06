#include "hero.hpp"

/**
 * Costruttore della classe
 * @param world il mondo in cui esisterà il tetramino
 */
Hero::Hero(World world): Tetramino(world, 4, 4) {}

/**
 * Stampa il tetramino nel suo frame attuale
 */
void Hero::print_frame() {
	Tetramino::print(frames[current]);
}

/**
 * Muove il tetramino in modo che non strabordi fuori dal mondo
 * @param dir positiva se a destra negativa altrimenti
 */
void Hero::safe_move(int dir) {
	if(!side_collisions(dir)) {
		int l_limit = (dir<0) * (XOFF - (current * 2) + 1);
		int r_limit = ((dir<0)*SCRW) + XOFF + SCRW + (current * 4) - WIDTH - 1;

		if(x > l_limit && x < r_limit)
			Tetramino::move(dir);
	}
}

/**
 * Ruota il tetramino di mezzo angolo giro
 */
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

/**
 * Controllo se ci sono ostacoli ai lati del tetramino
 */
int Hero::side_collisions(int side) {
	char c;
	int i, off, result = 0;

	if(current && side < 0)
		off = x + 1;
	if(current && side > 0)
		off = x + 4;

	if(!current && side < 0)
		off = x - 1;
	if(!current && side > 0)
		off = x + WIDTH;

	if(current) {
		for(i=y; i<y+HEIGHT; i++) {
			c = mvinch(i, off) & A_CHARTEXT;
			if(c == '[' || c == ']') {
				result = 1;
				break;
			}
		}
	}
	else {
		c = mvinch(y+HEIGHT-1, off) & A_CHARTEXT;
		if(c == '[' || c == ']')
			result = 1;
	}

	return result;
}
