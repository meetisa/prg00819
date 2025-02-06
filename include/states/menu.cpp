#include "menu.hpp"

/**
 * Costruttore della classe
 */
Menu::Menu() : State() {
	CRS_YOFF = TEXT_YOFF+1;
	CRS_X = (TEXT_XOFF/2);

	options.init(
		"Nuova partita\nClassifica\nEsci", // lista divisa da \n
		ROW_SPACING, // spazio tra le righe
		TEXT_XOFF, // offset della x
		TEXT_YOFF, // offset della y
		"||--++++" // bordi della finestra
	);
	options.setInCenter();
}

/**
 * Stampa la finestra con il cursore e le opzioni
 */
void Menu::draw() {
	options.show_list();

	CRS_Y = cursor*ROW_SPACING + CRS_YOFF;

	wattron(options.win, A_BOLD);
	mvwprintw(options.win, CRS_Y, CRS_X, "%c", CRS_CH);
	wattroff(options.win, A_BOLD);
}

/**
 * Funzione che fa interagire l'utente con lo stato
 * in base all'input
 *
 * In questo caso la funzione serve a far muovere l'utente
 * con il cursore e farlo scegliere un'opzione
 * @param input il tasto che preme l'utente
 */
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
		options.destroy();
	}

	return 0;
}
