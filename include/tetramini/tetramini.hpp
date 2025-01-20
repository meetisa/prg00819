#ifndef TETRAMINI_HPP
#define TETRAMINI_HPP

#include <ncurses.h>
#include "../states/world.hpp"

/**
 * Classe astratta di un tetramino generico.
 */
class Tetramino {
	protected:
		int SCRW;
		int SCRH;
		int XOFF;

		int WIDTH;
		int HEIGHT;

		int STARTX=20;
		int STARTY=1;

		int x;
		int y;

		WINDOW *base;
	public:
		/// Costruttore della classe
		Tetramino(World world, int w, int h);

		/// Stampa il tetramino nel terminale
		void print(int shape);

		/// Funzione astratta
		virtual void print_frame()=0;

		/// Muove in tetramino a destra o a sinistra
		void move(int dir);

		/// Funzione astratta
		virtual void safe_move(int dir)=0;

		/// Simulazione della caduta del tetramino
		int falling();

		/// Morte del tetramino
		void dies();

		/// Funzione astratta
		virtual void rotate()=0;

		/// Controlla le collisioni del tetramino
		int check_collision();

		/// Fa sapere il contenuto di una riga del tetramino
		void getclout(int row, char *buffer);
};

#endif
