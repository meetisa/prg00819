#include "menu.hpp"

Menu::Menu() : State() {
	CRS_YOFF = TEXT_YOFF+1;
	CRS_X = TEXT_XOFF/2;

	options.init(
		"Nuova partita\nClassifica\nEsci", // lista divisa da \n
		ROW_SPACING, // spazio tra le righe
		TEXT_XOFF, // offset della x
		TEXT_YOFF, // offset della y
		"||--++++" // bordi della finestra
	);
	options.setInCenter();
}

void Menu::draw() {
	options.show_list();

	CRS_Y = cursor*ROW_SPACING + CRS_YOFF;

	wattron(options.win, A_BOLD);
	mvwprintw(options.win, CRS_Y, CRS_X, "%c", CRS_CH);
	wattroff(options.win, A_BOLD);
}

int Menu::update(int input) {

	int len = options.get_len();

	if(input == KEY_DOWN || input == KEY_UP) {
		// Cancello il vecchio cursore
		mvwprintw(options.win, CRS_Y, CRS_X, " ");

		// Aggiorno in quale opzione è la il cursore
		cursor += 1 -2*(input==KEY_UP);

		// Per ciclare il c
		if(cursor >= len)
			cursor = 0;
		if(cursor < 0)
			cursor = len-1;

		// Aggiiorno la posizione del cursore nello schermo
		CRS_Y = cursor*ROW_SPACING + CRS_YOFF;

		// Stampo il cursore nuovo
		wattron(options.win, A_BOLD);
		mvwprintw(options.win, CRS_Y, CRS_X, "%c", CRS_CH);
		wattroff(options.win, A_BOLD);
	}

	draw();

	if(input == ' ') {
		if(cursor==0)
			setNext(PARTITA);
		if(cursor==1)
			setNext(CLASSIFICA);
		if(cursor==2)
			Quit();

		setDone(1);
		werase(options.win);
		delwin(options.win);
	}

	return 0;
}
