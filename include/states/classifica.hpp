#ifndef CLASSIFICA_HPP
#define CLASSIFICA_HPP

#include <string.h>
#include <fstream>
#include <ncurses.h>
#include "../state_machine/abstract_state.hpp"
using namespace std;

typedef struct pnode {
	pnode *next;
	char name[50];
	int points;
} player;

class Classifica : public State {
	private:
		const char *filename = "classifica.txt";
		ofstream ofile;
		ifstream ifile;

		player *head = new player;

		int WIDTH, HEIGHT;
		int STARTX, STARTY;
		WINDOW *win;

		const int ROW_SPACING = 2;
		const int TEXT_XOFF = 2;
		const int TEXT_YOFF = 2;
		int length=0;

	public:
		Classifica();
		int update(int input);

		void display();
		player gameOverScreen(int points);

		void addPlayer(player p);
};

#endif
