#include "world.hpp"

World::World(int w, int h, int xoff) {
	SCRW = w;
	SCRH = h;
	XOFF = xoff;
	screen = newwin(SCRH, SCRW, 0, XOFF);

	points_scr = newwin(PNT_SCRH, PNT_SCRW, PNT_SCRY, PNT_SCRX);

	GRIDW = (SCRW/2) - 1;
	GRIDH = SCRH - 2;

	LEN = GRIDW * GRIDH;
	GRID_XOFF += XOFF;

	grid = new block;
	grid->val = 0;
	grid->row_blocks = -1;
	grid->next = NULL;
}

void World::getspecs(int *w, int *h, int *xoff) {
	*w = SCRW;
	*h = SCRH;
	*xoff = XOFF;
}

void World::pos_to_coords(int pos, int *x, int *y) {
	*x = ((pos % GRIDW) * 2) + GRID_XOFF;
	*y = (pos / GRIDW) + GRID_YOFF;
}

void World::draw() {
	block *iter;
	int pos=LEN-1, x, y, l=0;
	int row=GRIDH;

	for(iter=grid; iter!=NULL; iter=iter->next) {
		pos_to_coords(pos--, &x, &y);
		if(iter->val)
			mvprintw(y, x, "[]");
		l++;
	}
}

void World::scan() {
	char ch;
	int pos, x, y;
	int emptyrow = 0;
	int row=0;
	int c=0;

	block *iter;
	iter=grid;
	for(pos=LEN-1; pos>0; pos--) {
		pos_to_coords(pos, &x, &y);

		ch = mvinch(y, x) & A_CHARTEXT;

		if(ch == '[') {
			iter->val=1;
			emptyrow=0;
			c++;
		}
		else {
			iter->val=0;
			emptyrow++;
		}

		if(iter->next==NULL) {
			iter->next = new block;
			iter->next->next = NULL;
			iter->next->val = 0;
			iter->next->row_blocks = -1;
		}

		if(pos % GRIDW == 0) {
			iter->row_blocks = c;
			c = 0;
		}

		if(emptyrow > GRIDW*2)
			break;

		iter = iter->next;
	}
}

int World::checkfullrow() {
	block *iter;
	block *prev_row;
	block *pivot;

	int points=0;
	int row=0;
	int streak=0;

	for(iter=grid; iter->next!=NULL; iter=iter->next) {
		if(iter->row_blocks >= 0) {

			if(row==0)
				prev_row = iter;

			if(iter->row_blocks == GRIDW) {
				streak++;
				if(prev_row->row_blocks != GRIDW)
					pivot = prev_row;
			}
			else {
				if(prev_row->row_blocks == GRIDW) {
					if(row-streak == 0)
						grid = prev_row->next;
					else
						pivot->next = prev_row->next;
					points += 10 * streak*streak;
					streak=0;
					clear();
				}
			}

			row++;
			prev_row = iter;
		}
	}

	return points;
}

void World::update_screen() {
	wborder(screen, '|', '|', '#', '#', '+', '+', '+', '+');
	wrefresh(screen);
}

void World::update_points(int p) {
	wborder(points_scr, '|', '|', '-', '-', '+', '+', '+', '+');
	mvwprintw(points_scr, 1, 1, "punteggio: %d", p);
	wrefresh(points_scr);
}
