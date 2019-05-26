#include "cell.h"

Cell::Cell(int px, int py, bool pb) {
	x = px;
	y = py;
	isAlive = pb;
	liveAdj = 0;
}

int Cell::getX() {
	return x;
}

int Cell::getY() {
	return y;
}