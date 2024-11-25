#include "menu.hpp"

Menu::Menu() : State() {

	int maxw, maxh;

	WIDTH = 40;
	/*
	 * il +1 serve per avere una riga vuota
	 * all'inizio e una alla fine (*2 +1),
	 * mentre il +2 sono i bordi sopra e sotto
	 */
	HEIGHT = OPT_LEN*ROW_SPACING +1 +2;

	getmaxyx(stdscr, maxh, maxw);
	STARTY = (maxh/2) - (HEIGHT/2);
	STARTX = (maxw/2) - (WIDTH/2);

	win = newwin(HEIGHT, WIDTH, STARTY, STARTX);

	// opt.init(WIDTH, HEIGHT, STARTY, STARTX, "||--++++");
	// char o[] = "Nuova partita\nClassifica";
	// opt.init_text(o, 2, ROW_SPACING, TEXT_XOFF, TEXT_YOFF);
}

void Menu::draw() {
	// opt.show_list();

	wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
	for(int i=0; i<OPT_LEN; i++) {
		mvwprintw(win, i*ROW_SPACING + TEXT_YOFF, TEXT_XOFF, "%s", options[i]);
	}

	CRS_Y = cursor*ROW_SPACING + CRS_YOFF;
	mvwprintw(win, CRS_Y, CRS_X, "%c", CRS_CH);
}

int Menu::update(int input) {

	if(input == KEY_DOWN || input == KEY_UP) {
		mvwprintw(win, CRS_Y, CRS_X, " ");

		cursor++;
		if(cursor >= OPT_LEN)
			cursor = 0;

		CRS_Y = cursor*ROW_SPACING + CRS_YOFF;
		wattron(win, A_BOLD);

		mvwprintw(win, CRS_Y, CRS_X, "%c", CRS_CH);

		wattroff(win, A_BOLD);
	}


	draw();

	wrefresh(win);

	if(input == ' ') {
		if(cursor)
			setNext(CLASSIFICA);
		else
			setNext(PARTITA);

		setDone(1);
		werase(win);
		wrefresh(win);
		delwin(win);
	}


	return 0;
}
