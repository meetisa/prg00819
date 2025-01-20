#ifndef SMASHBOY_HPP
#define SMASHBOY_HPP

#include "../states/world.hpp"

/**
 * Tetramino di forma quadrata, chiamato con il nome originale
 */
class Smashboy: public Tetramino {
	protected:
		int frame = 15;
		//char frame[5] = "1111";

	public:
		/// Costruttore del tetramino
		Smashboy(World world);

		/// Stampa il tetramino nel suo frame attuale
		void print_frame();

		/// Muove il tetramino senza farlo uscire dal mondo
		void safe_move(int dir);

		/// Ruota il tetramino di zero gradi
		void rotate() {}
};

#endif
