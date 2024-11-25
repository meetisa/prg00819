CMP=g++

IDIR = ./include

TETR_DIR = $(IDIR)/tetramini
STATES_DIR = $(IDIR)/states
STATE_MACHINE_DIR = $(IDIR)/state_machine

ODIR = ./obj

_OBJ = tetramini.o hero.o smashboy.o \
	gameplay.o world.o menu.o classifica.o screen.o \
	abstract_state.o abstract_state-machine.o
OBJ = $(patsubst %,  $(ODIR)/%, $(_OBJ))

FLAGS=-lncurses -I/$(TETR_DIR) -I/$(STATES_DIR) -Wall -Wextra -g

# include/state_machine
$(ODIR)/%.o: $(STATE_MACHINE_DIR)/%.cpp $(STATE_MACHINE_DIR)/%.hpp
	$(CMP) -c $< -o $@ $(FLAGS)

# include/states
$(ODIR)/%.o: $(STATES_DIR)/%.cpp $(STATES_DIR)/%.hpp
	$(CMP) -c $< -o $@ $(FLAGS)

# include/tetramini
$(ODIR)/%.o: $(TETR_DIR)/%.cpp $(TETR_DIR)/%.hpp
	$(CMP) -c $< -o $@ $(FLAGS)

# main
tetris: tetris.cpp $(OBJ)
	$(CMP) -o $@ $^ $(FLAGS) && ./$@

# t: t.cpp
# 	$(CMP) -o $@ $^ -lncurses $(FLAGS)
