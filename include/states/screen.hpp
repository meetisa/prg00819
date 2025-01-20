#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <string.h>
#include <ncurses.h>

/**
 * Per scrivere efficientemente
 * le liste di stringhe in una finestra
 */
typedef struct f {
	char *str[50];
	int max_len;
} field;

/**
 * Raggruppa tutte le funzioni utili per gestire una finestra ncurses
 */
class Screen {
	protected:
		int WIDTH, HEIGHT;
		int STARTY, STARTX;
		char BORDERS[8];

	public:

		WINDOW *win;

		/// Costruttore della classe
		Screen(){};

		/// Inizializza la finestra
		void init(int w, int h, int stx, int sty, char borders[]);

		/// Centra la finestra nel terminale
		void setInCenter();

		/// Stampa la finestra
		void show();

		/// Cancella la finestra
		void destroy();
};

/**
 * Classe figlia per le finestre che stampano una lista di stringhe
 */
class List : public Screen {
	private:
		int LENGTH;
		int ROW_SPACING;
		int TEXT_XOFF;
		int TEXT_YOFF;

		int TOTAL_CHARS_LEN;

		char *list = NULL;
		char splitter;
		const char cols_d = '@';
		const char rows_d = '\n';

		int NFIELDS=0;

		field *f;

	public:

		/// Costruttore della classe
		List(){};

		/// Inizializza la finestra
		void init(char text[], char delimiter, int r_s, int txt_xoff, int txt_yoff, char borders[]);

		/// Aggiorna larghezza e altezza
		void compute_sizes(int *width, int *height);

		/// Aggiorna la lista di stringhe da stampare
		void update_list(char new_text[]);

		/// Stampa la finestra e la lista di stringhe
		void show_list();

		/// Fa sapere la lunghezza della lista di stringhe
		int get_len();
};

#endif
