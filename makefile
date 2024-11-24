CMP=g++

IDIR = ./include
TETR_DIR = $(IDIR)/tetramini
STATES_DIR = $(IDIR)/states

ODIR = ./obj

_OBJ = tetramini.o gameplay.o hero.o smashboy.o world.o menu.o classifica.o state.o state_machine.o
OBJ = $(patsubst %,  $(ODIR)/%, $(_OBJ))

FLAGS=-lncurses -I/$(TETR_DIR) -I/$(STATES_DIR) -Wall -Wextra -g

$(ODIR)/%.o: $(STATES_DIR)/%.cpp $(STATES_DIR)/%.hpp
	$(CMP) -c $< -o $@ $(FLAGS)

$(ODIR)/%.o: $(TETR_DIR)/%.cpp $(TETR_DIR)/%.hpp
	$(CMP) -c $< -o $@ $(FLAGS)

tetris: tetris.cpp $(OBJ)
	$(CMP) -o $@ $^ $(FLAGS) && ./$@

# t: t.cpp
# 	$(CMP) -o $@ $^ -lncurses -Wall -Wextra -Werror -g
