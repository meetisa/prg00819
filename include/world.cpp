#include "world.hpp"

World::World(int w, int h, int xoff) {
	SCRW = w;
	SCRH = h;
	XOFF = xoff;
	screen = newwin(SCRH, SCRW, 0, XOFF);

	GRIDW = (SCRW/2)-1;
	GRIDH = SCRH-2;

	LEN = GRIDW * GRIDH;
	grid = new int[LEN];
	for(int i=0; i<LEN; i++)
		grid[i] = 0;
}

void World::getspecs(int *w, int *h, int *xoff) {
	*w = SCRW;
	*h = SCRH;
	*xoff = XOFF;
}

int World::coords_to_pos(int x, int y) {
	return ((y-1)*GRIDW) + x;
}

void World::pos_to_coords(int pos, int *x, int *y) {
	*x = pos % GRIDW;
	*y = pos / GRIDW;
}

void World::draw() {
	int x, y;
	int c=0;
	for(int i=0; i<LEN; i++) {
		pos_to_coords(i, &x, &y);
		if(grid[i])
			//2+ è l'offset del mondo
			mvprintw(y+1, (x*2)+1, "[]");
	}
}

void World::update_screen() {
	wborder(screen, '|', '|', '#', '#', '+', '+', '+', '+');
	wrefresh(screen);
}

/*
void World::suckup(Hero t) {
	int x, y;
	t.getcoords(&x, &y);

	char b[8];
	for(int i=0; i<4; i++) {
		t.getclout(i, b);
		for(int j=0; j<8; j=j+2) {
			if(b[j] == '[') {
				t.getcoords(&x, &y);
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

}
*/

void World::checkfullrow() {
	int bl;
	for(int r=GRIDH; r>0; r--) {
		bl = 0;
		for(int c=0; c<GRIDW; c++) {
			int p = coords_to_pos(c, r);
			bl += grid[p];
		}
		if(bl == 0)
			break;
		if(bl == GRIDW) {
			for(int i=0; i<GRIDW; i++) {
				int p = coords_to_pos(i, r);
				grid[p] = 0;
			}

			int bl2;
			for(int i=r-1; i>0; i--) {
				bl2 = 0;
				int p;
				for(int j=0; j<GRIDW; j++) {
					p = coords_to_pos(j, i);
					if(grid[p]) {
						bl2++;
						grid[p+GRIDW] = 1;
						grid[p] = 0;
					}
				}
				if(bl2 == 0)
					break;
				mvprintw(r, 50, "%d", r);

			}

		}
		mvprintw(r, 43, "%d", bl);
	}
}
