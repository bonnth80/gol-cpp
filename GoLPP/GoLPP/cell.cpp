#include "cell.h"

Cell::Cell(int px, int py) {
	x = px;
	y = py;
	neighbors = 0;
}

// Accessors ********************************
int Cell::getX() {return x;}
int Cell::getY() {return y;}
int Cell::getNeighbors() { return neighbors; }

// Mutators *********************************
void Cell::setX(int pX) { x = pX; };
void Cell::setY(int pY) { y = pY; };
void Cell::setNeighbors(int pLN) { neighbors = pLN; }

// Operators ********************************
bool Cell::operator==(Cell cRight) {
	return (x == cRight.x && y == cRight.y);
}

bool Cell::operator!=(Cell cRight) {
	return (x != cRight.x || y != cRight.y);
}

bool Cell::operator>(Cell cRight) {
	if (x > cRight.x)
		return true;
	else
		return (x == cRight.x && y > cRight.y);
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
		return (x == cRight.x && y < cRight.y);
}

bool Cell::operator<=(Cell cRight) {
	if (x < cRight.x)
		return true;
	else
		return (x == cRight.x && y <= cRight.y);
}

Cell Cell::operator++(int cRight) {
	Cell temp(x, y);
	temp.neighbors = neighbors;
	neighbors++;
	return temp;
}

Cell Cell::operator++() {
	neighbors++;
	return *this;
}