#ifndef MENU_HPP
#define MENU_HPP

#include <ncurses.h>

#define OPT_LEN 2

class Menu {
	private:
		int WIDTH = 40;
		int HEIGHT = OPT_LEN*2 + 1 + 2;
		int STARTX, STARTY;

		WINDOW *win;

		const char *options[OPT_LEN] = {"Nuova partita", "Classifica"};

		char CRS_CH = '>';
		int CRS_X = 2;
		int CRS_Y;
		int cursor = 0;

	public:
		Menu();
		int choose(int input);
};

#endif
