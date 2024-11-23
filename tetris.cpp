#include <iostream>
#include <ctime>
#include <ncurses.h>
#include "include/tetramini/tetramini.hpp"
#include "include/states/gameplay.hpp"
#include "include/states/menu.hpp"
#include "include/states/classifica.hpp"
#include "include/states/state_machine"

#define CLOCK 1000000

using namespace std;

int main(int argc, char *argv[]) {

	srand(time(NULL));

	clock_t tm = clock();
	double timer;
	double vel = CLOCKS_PER_SEC / 10;

	int input=0;
	int tick=0;
	int done = 0;

	int currentState = MENU;

	//initialization functions
	initscr();
	start_color();
	raw();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);

	curs_set(0); //invisible cursor

	const char *file_classifica = "classifica.txt";

	// auto p = Partita();
	// auto m = Menu();
	// auto c = Classifica();

	auto machine = StateMachine();

	int chosen=0;

	while(!done) {
		timer = (double) (clock() - tm) / vel;
		if(timer >= 1) {
			tm = clock();
			tick = 1;
		}
		else
			tick = 0;

		input = getch();

		//modo di uscire dal gioco
		if(input == 'q')
			done = 1;

		switch(currentState) {
			case MENU:
				chosen = m.choose(input);

				if(chosen == 0) {
					currentState = PARTITA;
					clear();
				}
				else if(chosen == 1) {
					currentState = CLASSIFICA;
					clear();
				}

			break;

			case PARTITA:
				if(p.gameplay(input, tick) == 0) {
					currentState = CLASSIFICA;
					clear();
				}
			break;

			case CLASSIFICA:
				c.display();
			break;
		}
	}

	endwin();
	return 0;
}
