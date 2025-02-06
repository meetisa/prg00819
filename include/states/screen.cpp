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
void Screen::init(int w, int h, int stx, int sty, const char borders[]) {
	WIDTH = w;
	HEIGHT = h;

	STARTX = stx;
	STARTY = sty;

	strcpy(BORDERS, borders);

	win = newwin(HEIGHT, WIDTH, STARTY, STARTX);
}

/**
 * Per centrare la finestra nel terminale
 */
void Screen::setInCenter() {
	int maxh, maxw;
	getmaxyx(stdscr, maxh, maxw);

	int middle_y = (maxh - HEIGHT) / 2;
	int middle_x = (maxw - WIDTH) / 2;

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
void List::init(char text[], int r_s, int txt_xoff, int txt_yoff, const char borders[]) {
	int w, h;

	ROW_SPACING = r_s;
	TEXT_XOFF = txt_xoff;
	TEXT_YOFF = txt_yoff;

	tot_ch_len = strlen(text);

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

	int i, xt=0, len=0;

	fields_len=1;
	rows=0;

	for(i=0; list[i] != rows_d; i++)  {
		fields_len += (list[i] == cols_d);
	}

	max_field_len = new int[fields_len];

	for(i=0; i<fields_len; i++)
		max_field_len[i] = 0;

	for(i=0; i<tot_ch_len; i++) {
		if(list[i] == rows_d || list[i] == cols_d) {
			if(len > max_field_len[xt])
				max_field_len[xt] = len;

			if(list[i] == rows_d) {
				rows++;
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
	for(i=0; i<fields_len; i++)
		*width += max_field_len[i];


	*width += (fields_len-1) + 2 + TEXT_XOFF*2 * fields_len;

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
	*height = (TEXT_YOFF*2) +2 +(rows*ROW_SPACING)-(ROW_SPACING-1);
}

/**
 * Aggiorna la lista di stringhe da stampare
 * @param new_text[] la nuova lista di stringhe
 */
void List::update_list(char new_text[]) {
	int w, h;

	tot_ch_len = strlen(new_text);
	list = new char[tot_ch_len];
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

	for(i=0; i<tot_ch_len; i++) {
		if(list[i] == rows_d) {
			y += ROW_SPACING;
			x = TEXT_XOFF;
			ch_x = 1;
			xt = 0;
		}
		else if(list[i] == cols_d) {
			x += 1+TEXT_XOFF*2 + max_field_len[xt];
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
	return rows;
}
