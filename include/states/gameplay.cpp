#include <ctime>
#include "gameplay.hpp"

#define SCREEN_WIDTH 42

#define X_OFFSET 2

/**
 * Costruttore della classe
 */
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

/**
 * Funzione per far interagire l'utente con lo stato di gioco
 * @param input il tasto che preme l'utente
 */
int Partita::update(int input) {
	if(game_over)
		gameOver();
	else
		gameplay(input);

	return 0;
}

/**
 * Fa procedere la partita e muove il tetramino
 * secondo le regole del gioco
 * @param input il tasto che preme l'utente
 * @returns se la partita è finita o no
 */
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

/**
 * In caso di game over bisogna aggiornare la classifica
 */
void Partita::gameOver() {
	time_t dt;
	time(&dt);
	struct tm *date;
	date = gmtime(&dt);

	points = rand() % 5000;

	fstream classifica;
	classifica.open("classifica.txt", fstream::app);
	classifica << points << '@' << date->tm_mday << '/' << date->tm_mon + 1 << '/' << 1900 + date->tm_year;
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
