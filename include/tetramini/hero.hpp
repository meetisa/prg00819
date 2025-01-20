#ifndef HERO_HPP
#define HERO_HPP

#include <iostream>
#include "tetramini.hpp"
#include "../states/world.hpp"

#define FRLEN 2

/**
 * Tetramino verticale, chiamato con il nome originale
 */
class Hero: public Tetramino {
	protected:
		long int frames[FRLEN] = {
			61440, 8738
			//4369, 8738, 17476, 34952,
			//15, 240, 3840, 61440
		};
		int current=0;
	public:
		/// Costruttore del tetramino
		Hero(World world);

		/// Stampa il tetramino nel suo frame attuale
		void print_frame();

		/// Muove il tetramino senza farlo uscire dal mondo
		void safe_move(int dir);

		/// Ruota il tetramino di mezzo angolo giro
		void rotate();

		/// Controlla che non ci siano ostacoli ai lati
		int side_collisions();
};

#endif
