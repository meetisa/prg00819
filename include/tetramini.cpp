#include "tetramini.hpp"

Tetramino::Tetramino(int coords) {
	id = coords;
	base = newwin(HEIGHT, WIDTH, y, x);
}

void Tetramino::print() {
	int tmp=id, dg, i=0, j=0;
	while(tmp!=0) {
		dg = tmp % 16;
		while(dg!=0) {
			if(dg % 2)
				mvprintw(y+i, x+j*2, "[]");
			dg /= 2;
			j++;
		}
		tmp /= 16;
		i++;
		j=0;
	}

	refresh();
	wrefresh(base);
}

void Tetramino::clear() {
	for(int i=0; i<HEIGHT; i++)
		for(int j=0; j<WIDTH; j++)
			mvprintw(y+i, x+j, " ");
}
