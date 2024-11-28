#ifndef CLASSIFICA_HPP
#define CLASSIFICA_HPP

#include <string.h>
#include <fstream>
#include <ncurses.h>
#include "../state_machine/abstract_state.hpp"
#include "screen.hpp"
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

		char *players;

		List chart;

		int ROW_SPACING = 2;
		int TEXT_XOFF = 3;
		int TEXT_YOFF = 1;
		int length=0;

	public:
		Classifica();
		int update(int input);

		void display();
		player gameOverScreen(int points);

		void addPlayer();
};

#endif
