#include <ctime>
#include "world.hpp"
#include "tetramini.hpp"
#include "hero.hpp"
#include "smashboy.hpp"
#include "gameplay.hpp"

#define VELOCITY_MOD 10
#define SCREEN_WIDTH 42

#define X_OFFSET 2

int gameplay() {
	//int tm=0;

	clock_t tm;
	tm=clock();
	double timer;
	double vel = CLOCKS_PER_SEC / VELOCITY_MOD;

	/*
	 * variabile per contenere il tasto premuto
	 * dal giocatore
	 */
	int command;


	int done = 0;

	/*
	 * per efficienza lo scherma si aggiorna
	 * solo quando il tetramino si sta muovendo
	 */
	int is_moving=0;

	// i punti della partita
	int points=0;

	//variabile contenente l'esito della caduta
	int falls;

	auto world = World(SCREEN_WIDTH, LINES, X_OFFSET);
	world.update_screen();
	world.update_points(points);

	/*
	 * si utilizza un puntatore alla classe base
	 * che punterà casualmente, a turno,
	 * una variabile della classe derivata
	 */
	Tetramino *t;

	Hero h(world);
	Smashboy s(world);

	//primo tetramino ad uscire in modo casuale
	if(rand() % 2) t = &h;
	else t = &s;

	while(!done) {
		timer = (double) (clock() - tm) / vel;

		t->print_frame();

		if(timer >= 1) {
			falls = t->falling();
			if(falls == 0) {
				t->dies();
				world.scan();
				points += world.checkfullrow();

				//scelta casuale del nuovo tetramino
				if(rand()%2) t = &h;
				else t = &s;
			}
			else if(falls == -1)
				//game over
				return points;

			tm=clock();
			is_moving = 1;
		}

		command = getch();

		//per uscire dalla partita senza game over
		if(command == 'q')
			done = 1;

		//rotazione del tetramino
		else if(command == KEY_UP || command == KEY_DOWN)
			t->rotate();

		//movimento laterale
		else if(command == KEY_LEFT || command == KEY_RIGHT) {
			t->safe_move(2 - 4*(command == KEY_LEFT));
			is_moving = 1;
		}

		//aggiornamenti ad ogni movimento
		if(is_moving) {
			world.update_screen(); /* dello schermo di gioco */
			world.update_points(points); /* dello schermo dei punti */
			world.draw(); /* della griglia dei blocchi */
			is_moving = 0;
		}
	}

	//uscita manuale dalla partita
	return -1;
}
