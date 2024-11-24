#ifndef MENU_HPP
#define MENU_HPP

#include <ncurses.h>
#include "state.hpp"

#define OPT_LEN 2

class Menu : public State {
	private:

		int WIDTH, HEIGHT;
		int STARTX, STARTY;

		WINDOW *win;


		const int ROW_SPACING = 2;


		const char *options[OPT_LEN] = {
			"Nuova partita",
			"Classifica"
		};

		const int TEXT_XOFF = 4;
		const int TEXT_YOFF = 2;


		const char CRS_CH = '>';
		const int CRS_YOFF = 2;
		const int CRS_X = 2;
		int CRS_Y;
		int cursor = 0;

	public:
		Menu();

		void draw();

		int update(int input);
};

#endif
