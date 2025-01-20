#ifndef GRID_HPP
#define GRID_HPP

#include <ncurses.h>

/**
 * Lista concatenata
 * rappresenta un singolo blocco di tetris
 */
typedef struct node {
	node *next;
	int val;
	int row_blocks;
} block;

/**
 * Il mondo di tetris che gestisce le interazioni tra
 * tetramino e l'esterno
 */
class World {
	private:
		//dimensioni dello schermo di gioco
		int SCRW, SCRH;

		//differenza di posizione rispetto all'origine
		int XOFF;

		WINDOW *screen;


		//dimesioni dello schermo dei punti
		int PNT_SCRW = 25;
		int PNT_SCRH = 3;

		//posizione dello schermo dei punti
		int PNT_SCRX = 50;
		int PNT_SCRY = 2;

		WINDOW *points_scr;


		/*
		 * differenze di posizione dei blocchi
		 * rispetto allo schermo di gioco
		 */
		int GRID_XOFF=1;
		int GRID_YOFF=1;

		//dimensioni della griglia
		int GRIDW;
		int GRIDH;
		int LEN;

		//la griglia è una lista concatenata
		block *grid;

	public:
		/// Costruttore della classe
		World(int w, int h, int xoff);

		/// Fa sapere le specifiche del mondo di gioco
		void getspecs(int *w,  int *h, int *xoff);

		/// Converte la posizione nella griglia in coordinate reali
		void pos_to_coords(int pos, int *x, int *y);

		/// Stampa il mondo nel terminale
		void draw();

		/// Scannerizza tutto il mondo e aggiorna la griglia
		void scan();

		/// Controlla se ci sono righe piene
		int checkfullrow();

		/// Aggiorna la finestra
		void update_screen();

		/// Aggiorna il punteggio a schermo
		void update_points(int p);

};

#endif
