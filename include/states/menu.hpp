#ifndef MENU_HPP
#define MENU_HPP

#include <ncurses.h>
#include "../state_machine/abstract_state.hpp"
#include "screen.hpp"

class Menu : public State {
	private:
		int ROW_SPACING = 2;

		List options;

		int TEXT_XOFF = 6;
		int TEXT_YOFF = 1;

		const char CRS_CH = '>';
		int CRS_YOFF;
		int CRS_X;
		int CRS_Y;
		int cursor = 0;

	public:
		Menu();

		void draw();

		int update(int input);
};

#endif
