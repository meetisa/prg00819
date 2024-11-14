#include <iostream>
#include "tetramini.hpp"

Tetramino::Tetramino(World world, int w, int h) {
	WIDTH = w*2;
	HEIGHT = h;

	world.getspecs(&SCRW, &SCRH, &XOFF);

	STARTX = SCRW / 2;

	base = newwin(HEIGHT, WIDTH, y, x);
}

void Tetramino::print(int shape) {
	int i, c=0;
	for(i=shape; i!=0; i/=2, c++) {
		if(i % 2)
			mvwprintw(base, c/HEIGHT, (c%HEIGHT)*2, "[]");
	}
	wrefresh(base);
}

void Tetramino::move(int dir) {
	x += dir;
	mvwin(base, y, x);
	wrefresh(base);
}

int Tetramino::falling() {
	if(!check_collision() && y < SCRH - (HEIGHT+1)) {
		y += 1;
		mvwin(base, y, x);
		wrefresh(base);
		return 1;
	}
	else
		return 0;
}

void Tetramino::dies() {
	char b[WIDTH];
	int i, j, pos;
	for(i=0; i<HEIGHT; i++) {
		getclout(i, b);
		for(j=0; j<WIDTH; j=j+2) {
			if(b[j] == '[') {
				mvprintw(y+i, x+j, "[]");
			}
		}
	}
}

void Tetramino::getcoords(int *wx, int *wy) {
	*wx = x;
	*wy = y;
}

int Tetramino::check_collision() {
	int x, y;
	getcoords(&x, &y);

	char b[WIDTH+1];
	getclout(HEIGHT-1, b);

	int coll = 0;
	char ch;
	for(int i=0; i<WIDTH; i++) {
		ch = mvinch(y+HEIGHT, x+i) & A_CHARTEXT;
		if(b[i] == '[' && ch == '[') {
			coll = 1;
			break;
		}
	}

	return coll;
}

void Tetramino::getspecs(int *width, int *height) {
	*width = WIDTH;
	*height = HEIGHT;
}

void Tetramino::getclout(int row, char *buffer) {
	for(int i=0; i<WIDTH+1; i++)
		buffer[i] = mvwinch(base, row, i) & A_CHARTEXT;
	buffer[WIDTH] = '\0';
}

void Tetramino::del() {
	x = STARTX;
	y = STARTY;
}
