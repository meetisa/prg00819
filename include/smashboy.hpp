#ifndef SMASHBOY_HPP
#define SMASHBOY_HPP

class Smashboy: public Tetramino {
	protected:
		int frame = 15;
		//char frame[5] = "1111";

	public:
		Smashboy();
		void print();
		void rotate() {}
};

#endif
