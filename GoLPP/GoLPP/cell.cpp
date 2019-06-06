#include "cell.h"

Cell::Cell(int col, int row) {
	x = col;
	y = row;
	isAlive = false;

	for (int i = 0; i < 8; i++) {
		neighborhood[i] = nullptr;
	}
}

int Cell::getX() { return x; }
int Cell::getY() { return y; }
bool Cell::getIsAlive() { return isAlive; }

Cell * Cell::getNeighbor(int index) {
	return neighborhood[index];
}


void Cell::setNeighbor(int position, Cell * c) {
	neighborhood[position] = c;
}

void Cell::setIsAlive(bool alive) {
	isAlive = alive;
}

void Cell::toggleIsAlive() {
	isAlive = !isAlive;
}