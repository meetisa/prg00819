#include "screen.hpp"

/* SCREEN */

/**
 * Inizializza la finestra principale
 * @param w la larghezza della finestra
 * @param h l'alezza della finestra
 * @param stx l'ascissa di partenza della finestra
 * @param sty l'ordinata di partenza della finestra
 * @param borders stringa di 8 caratteri che sono i bordi della finestra
 */
void Screen::init(int w, int h, int stx, int sty, char *borders) {
	WIDTH = w;
	HEIGHT = h;

	STARTX = stx;
	STARTY = sty;

	strcpy(BORDERS, borders);

	win = newwin(HEIGHT, WIDTH, STARTY, STARTX);
}

/**
 * Per centra la finestra nel terminale
 */
void Screen::setInCenter() {
	int maxh, maxw;
	getmaxyx(stdscr, maxh, maxw);

	int middle_y = (maxh/2) - (HEIGHT/2);
	int middle_x = (maxw/2) - (WIDTH/2);

	mvwin(win, middle_y, middle_x);
}

/**
 * Stampa la finestra, con i suoi bordi e il suo contenuto
 */
void Screen::show() {
	wborder(
		win,
		BORDERS[0],
		BORDERS[1],
		BORDERS[2],
		BORDERS[3],
		BORDERS[4],
		BORDERS[5],
		BORDERS[6],
		BORDERS[7]
	);

	wrefresh(win);
}

/**
 * Cancella e distrugge la finestra
 */
void Screen::destroy() {
	werase(win);
	wrefresh(win);
	//delwin(win);
}

/* LIST */

/**
 * Inizializza tutte le proprietà principali della classe
 * @param text[] la lista di stringhe iniziali da stampare
 * @param r_s quante righe vuote tra una stringa e l'altra
 * @param txt_xoff quanto spazio tra i bordi verticali
 * @param txt_yoff quanto spazio tra i bordi orizzontali
 * @param borders stringa di 8 caratteri che sono i bordi della finestra
 */
void List::init(char text[], int r_s, int txt_xoff, int txt_yoff, char borders[]) {
	int w, h;

	ROW_SPACING = r_s;
	TEXT_XOFF = txt_xoff;
	TEXT_YOFF = txt_yoff;

	TOTAL_CHARS_LEN = strlen(text);

	list = text;

	compute_sizes(&w, &h);

	Screen::init(w, h, 0, 0, borders);
}

/**
 * In base alla lista di stringhe attuali calcola una nuova
 * larghezza e altezza della finestra
 * @param[out] width la nuova larghezza
 * @param[out] height la nuova altezza
 */
void List::compute_sizes(int *width, int *height) {

	/*

	 nota del futuro:
	 una scelta più efficiente sarebbe quella di
	 usare un parametro char *titles[] tipo
	 {"nome", "punteggio", "data"}
	 per potere avere già il numero di colonne e i titoli delle colonne

	 */


	int i, xt=0, len=0;

	NFIELDS=1;
	LENGTH=1;

	for(i=0; list[i] != rows_d; i++)  {
		NFIELDS += (list[i] == cols_d);
	}

	maxf = new int[NFIELDS];

	for(i=0; i<NFIELDS; i++)
		maxf[i] = 0;

	for(i=0; i<TOTAL_CHARS_LEN; i++) {
		if(list[i] == rows_d || list[i] == cols_d) {
			if(len > maxf[xt])
				maxf[xt] = len;

			if(list[i] == rows_d) {
				LENGTH++;
				len = 0;
				xt = 0;
			}

			if(list[i] == cols_d) {
				len = 0;
				xt++;
			}
		}
		else
			len++;
	}

	*width = 0;
	for(i=0; i<NFIELDS; i++)
		*width += maxf[i];


	*width += (NFIELDS-1) + 2 + TEXT_XOFF*2 * NFIELDS;

	/*
	 * | bordo sopra (+1)
	 * |--------------
	 * | +TEXT_YOFF sopra
	 * |--------------
	 * | (numero righe * spazio tra esse) - (spazio-1)
	 * |--------------
	 * | +TEXT_YOFF sotto
	 * |--------------
	 * | bordo sotto (+1)
	 */
	*height = (TEXT_YOFF*2) +2 +(LENGTH*ROW_SPACING)-(ROW_SPACING-1);
}

/**
 * Aggiorna la lista di stringhe da stampare
 * @param new_text[] la nuova lista di stringhe
 */
void List::update_list(char new_text[]) {
	int w, h;

	TOTAL_CHARS_LEN = strlen(new_text);
	list = new char[TOTAL_CHARS_LEN];
	list = new_text;

	compute_sizes(&w, &h);
	wresize(win, h, w);
}

/**
 * Stampa la finestra e la lista di stringhe
 */
void List::show_list() {

	int i, xt=0;
	int ch_x = 1;
	int y=TEXT_YOFF+1, x=TEXT_XOFF;

	for(i=0; i<TOTAL_CHARS_LEN; i++) {
		if(list[i] == rows_d) {
			y += ROW_SPACING;
			x = TEXT_XOFF;
			ch_x = 1;
			xt = 0;
		}
		else if(list[i] == cols_d) {
			x += 1+TEXT_XOFF*2 + maxf[xt];
			mvwprintw(win, y, x-TEXT_XOFF, "|");
			ch_x = 1;
			xt++;
		}
		else
			mvwprintw(win, y, x + ch_x++, "%c", list[i]);
	}

	Screen::show();
}

/**
 * Fa sapere la lunghezza della lista di stringhe
 * @returns la lunghezza della lista
 */
int List::get_len() {
	return LENGTH;
}
