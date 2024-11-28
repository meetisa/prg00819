#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <string.h>
#include <ncurses.h>

class Screen {
	protected:
		int WIDTH, HEIGHT;
		int STARTY, STARTX;
		char BORDERS[8];

	public:

		WINDOW *win;

		Screen(){};
		void init(int w, int h, int stx, int sty, char borders[]);
		void setInCenter();

		void show();
};

class List : public Screen {
	private:
		int LENGTH=1;
		int ROW_SPACING;
		int TEXT_XOFF;
		int TEXT_YOFF;

		int TOTAL_CHARS_LEN;

		char *list;

	public:

		List(){};

		void init(char text[], int r_s, int txt_xoff, int txt_yoff, char borders[]);

		void show_list();

		int get_len() {return LENGTH;}
};

#endif
