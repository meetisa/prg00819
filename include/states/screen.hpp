#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <string.h>
#include <ncurses.h>

class Screen {
	protected:
		int WIDTH, HEIGHT;
		int STARTY, STARTX;
		char BORDERS[8];

		WINDOW *win;

	public:
		Screen(){};
		void init(int w, int h, int stx, int sty, char borders[]);

		void show();
};

class List : public Screen {
	private:
		int LENGTH;
		int ROW_SPACING;
		int TEXT_XOFF;
		int TEXT_YOFF;

		char *list;

	public:

		List(){};

		void init(int w, int h, int stx, int sty, char borders[]);

		void init_text(char text[], int l, int r_s, int txt_xoff, int txt_yoff);

		void show_list();
};

#endif
