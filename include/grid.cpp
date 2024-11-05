#include "grid.hpp"

Grid::Grid(int w, int h) {
	width = (w-1)/2;
	height = h-2;
	len = width*height;
	grid = new int[len];
	for(int i=0; i<len; i++)
		grid[i] = 0;
}

int Grid::coords_to_pos(int x, int y) {
	return (y*width) + x;
}

void Grid::pos_to_coords(int pos, int *x, int *y) {
	*x = pos % width;
	*y = pos / width;
}

void Grid::draw() {
	int x, y;

	for(int i=0; i<len; i++) {
		pos_to_coords(i, &x, &y);
		if(grid[i])
			mvprintw(y+1, (x*2)+1, "[]");
	}
}

void Grid::suckup(Hero t) {
	int x, y;
	t.getcoords(&x, &y);

	char b[8];
	for(int i=0; i<4; i++) {
		t.getclout(i, b);
		mvprintw(36+i, 41, "%s", b);
		for(int j=0; j<8; j++) {
			mvprintw(0, 0, "%d\t%d", x, y);
			if(b[j] == '[') {
				int p = coords_to_pos((x+j)/2, y+i);
				grid[p] = 1;
			}
		}
	}
	/*
	char b;
	for(int r=height; r>0; r--) {
		int nb = 0;
		for(int c=0; c<width; c++) {
			b = mvinch(r, c) & A_CHARTEXT;
			mvprintw(r, 41+c, "%c", b);
			if(b == '[') {
				nb++;
				int p = coords_to_pos(c, r);
				grid[p] = 1;
			}

		}
		mvprintw(r, 41, "%d", nb);
		if(nb==0)
			break;
	}
	*/
}
