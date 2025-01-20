#include "state.hpp"

/**
 * Comunica che lo stato è a fine ciclo
 * e che bisogna passare al prossimo
 * @param d 1 se abbiamo finito 0 altrimenti
 */
void State::setDone(int d) {
	done = d;
}

/**
 * Per controllare se lo stato è finito
 * @returns se il valore è 0 o 1
 */
int State::isDone() {
	return done;
}

/**
 * Per poter decidere il prossimo stato di gioco
 * @param n il prossimo stato
 */
void State::setNext(state n) {
	next = n;
}

/**
 * Per vedere il prossimo stato di gioco
 * @returns il prossimo stato
 */
state State::getNext() {
	return next;
}

/**
 * Per decidere qual è lo stato precedente
 * @param lo stato precedente
 */
void State::setPrev(state prev) {
	previous = prev;
}

/**
 * Per uscire definitivamente dal gioco
 */
void State::Quit() {
	quit = 1;
}

/**
 * Per controllare se uscire dal gioco
 * @returns 0 se si resta 1 altrimenti
 */
int State::getQuit() {
	return quit;
}
