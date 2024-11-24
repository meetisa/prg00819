#ifndef CLASSIFICA_HPP
#define CLASSIFICA_HPP

#include <fstream>
#include <ncurses.h>
#include "state.hpp"
using namespace std;

class Classifica : public State {
	private:
		const char *filename = "classifica.txt";
		ofstream ofile;
		ifstream ifile;

		int WIDTH, HEIGHT;
		int STARTX, STARTY;
		WINDOW *win;

		const int ROW_SPACING = 2;
		const int TEXT_XOFF = 2;
		const int TEXT_YOFF = 2;
		int length=0;

	public:
		Classifica();
		void display();
		void addPlayer(char *name);

		int update(int input) {
			return input;

		}
};

#endif
