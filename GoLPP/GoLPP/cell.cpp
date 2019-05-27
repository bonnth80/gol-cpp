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

bool Cell::getAlive() {
	return isAlive;
}


// Operators ********************************

bool Cell::operator=(Cell cRight) {
	return (x == cRight.x && y == cRight.y);
}

bool Cell::operator>(Cell cRight) {
	if (x > cRight.x)
		return true;
	else
		return (y > cRight.y);
}

bool Cell::operator>=(Cell cRight) {
	if (x > cRight.x)
		return true;
	else
		return (x == cRight.x && y >= cRight.y);
}

bool Cell::operator<(Cell cRight) {
	if (x < cRight.x)
		return true;
	else
		return (y < cRight.y);
}

bool Cell::operator<=(Cell cRight) {
	if (x < cRight.x)
		return true;
	else
		return (x == cRight.x && y <= cRight.y);
}