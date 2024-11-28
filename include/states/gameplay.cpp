#include <ctime>
#include "gameplay.hpp"

#define SCREEN_WIDTH 42

#define X_OFFSET 2

Partita::Partita() : State() {

	setNext(CLASSIFICA);

	tm = clock();

	velocity = CLOCKS_PER_SEC / 10;


	world = new World(SCREEN_WIDTH, LINES, X_OFFSET);
	world->update_screen();
	world->update_points(points);

	h = new Hero(*world);
	s = new Smashboy(*world);

	//primo tetramino ad uscire in modo casuale
	if(rand() % 2)
		t = h;
	else
		t = s;
}


int Partita::update(int input) {
	gameOver();
	// gameplay(input);
	return 0;
}

int Partita::gameplay(int input) {

	timer = (double) (clock() - tm) / velocity;
	if(timer >= 1) {
		tm = clock();
		tick = 1;
	}
	else
		tick = 0;


	t->print_frame();

	//rotazione del tetramino
	if(input == KEY_UP || input == KEY_DOWN)
		t->rotate();

	//movimento laterale
	else if(input == KEY_LEFT || input == KEY_RIGHT) {
		t->safe_move(2 - 4*(input == KEY_LEFT));
		is_moving = 1;
	}

	if(tick) {
		falls = t->falling();
		if(falls == 0) {
			t->dies();
			world->scan();
			points += world->checkfullrow();

			//scelta casuale del nuovo tetramino
			if(rand()%2) t = h;
			else t = s;
		}
		// game over
		else if(falls == -1) {
			game_over = 1;

			return 0;
		}

		is_moving = 1;
	}

	//aggiornamenti ad ogni movimento
	if(is_moving) {
		world->update_screen(); /* dello schermo di gioco */
		world->update_points(points); /* dello schermo dei punti */
		world->draw(); /* della griglia dei blocchi */
		is_moving = 0;
	}

	//uscita manuale dalla partita
	 return -1;
}

void Partita::gameOver() {

	fstream classifica;
	classifica.open("classifica.txt", fstream::app);
	classifica << points;
	classifica.close();

	setDone(1);

	// echo();
 //
	// WINDOW *insert_name;
	// insert_name = newwin(3, 50, 3, 4);
	// wborder(insert_name, '|', '|', '-', '-', '+', '+', '+', '+');
 //
	// char name[50];
 //
	// mvwscanw(insert_name, 1, 1, "%s", name);
 //
	// wrefresh(insert_name);
 //
	// noecho();
 //
	// setNext(CLASSIFICA);
 //
	// setDone(1);
 //
	// return name;
}
