CMP=g++

IDIR = ./include
ODIR = ./obj

_OBJ = tetramini.o gameplay.o hero.o smashboy.o
OBJ = $(patsubst %,  $(ODIR)/%, $(_OBJ))

FLAGS=-lncurses -I/$(IDIR)

$(ODIR)/%.o: $(IDIR)/%.cpp $(IDIR)/%.hpp
	$(CMP) -c $< -o $@ $(FLAGS)

tetris: tetris.cpp $(OBJ)
	$(CMP) -o $@ $^ $(FLAGS) && ./$@
