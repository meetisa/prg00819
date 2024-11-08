#include "world.hpp"


World::World(int w, int h, int xoff) {
	SCRW = w;
	SCRH = h;
	XOFF = xoff;
	screen = newwin(SCRH, SCRW, 0, XOFF);

	GRIDW = (SCRW/2) - 1;
	GRIDH = SCRH - 2;

	LEN = GRIDW * GRIDH;
	GRID_XOFF += XOFF;

	grid = new block;
	grid->val = 0;
	grid->start_row = 1;
	grid->row_blocks = 0;
	grid->next = NULL;
	grid->prev = NULL;
}

void World::getspecs(int *w, int *h, int *xoff) {
	*w = SCRW;
	*h = SCRH;
	*xoff = XOFF;
}

/*
int World::coords_to_pos(int x, int y) {
	return (y-GRID_YOFF)*GRIDW + (x-GRID_XOFF)/2;
}
*/

void World::pos_to_coords(int pos, int *x, int *y) {
	*x = ((pos % GRIDW) * 2) + GRID_XOFF;
	*y = (pos / GRIDW) + GRID_YOFF;
}

void World::draw() {
	block *iter;
	int pos=LEN, x, y;
	for(iter=grid; iter!=NULL; iter=iter->next) {
		pos_to_coords(pos, &x, &y);
		if(iter->val)
			mvprintw(y, x, "[]");
		pos--;
	}
}

void World::scan() {
	char ch;
	int pos, x, y, prev_y=GRIDH;
	int emptyrow = 0;
	int fullrow = 0;
	int row = GRIDH;
	int *count;
	*count = grid->row_blocks;
	block *iter;
	iter=grid;
	for(pos=LEN; pos>0; pos--) {
		pos_to_coords(pos, &x, &y);

		if(iter->start_row) {
		//if(prev_y != y) {
			//mvprintw(prev_y, 50, "%d", fullrow);
			if(fullrow==GRIDW) {
				//mvprintw(2, 50, "fullrow %d", prev_y);
				block *iter2;
				iter2 = iter;
				int i;
				while(fullrow > 0 && iter2!=NULL) {
					iter2 = iter2->prev;
					fullrow--;
				}
				iter2->next = iter;
			}
			fullrow=0;
		}

		ch = mvinch(y, x) & A_CHARTEXT;

		if(ch == '[') {
			iter->val=1;
			emptyrow=0;
			fullrow++;
			*count++;
		}
		else {
			iter->val=0;
			emptyrow++;
		}

		if(iter->next==NULL) {
			iter->next = new block;
			iter->next->next = NULL;
			iter->next->prev = iter;
			iter->start_row = (pos%GRIDW == 0);
			iter->row_blocks = 0;
		}
		if(iter->start_row) {
			*count = iter->row_blocks;
			mvprintw(row--, 50, "%d", *count);
		}
		iter = iter->next;

		prev_y = y;

		if(emptyrow > GRIDW*2)
			break;
	}
}

void World::checkfullrow() {

}

void World::update_screen() {
	wborder(screen, '|', '|', '#', '#', '+', '+', '+', '+');
	wrefresh(screen);
}
