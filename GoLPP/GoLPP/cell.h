#pragma once

class Cell {
private:
	int x;
	int y;
	int neighbors;
public:
	// constructor
	Cell() {
		x = 0;
		y = 0;
		neighbors = 0;
	}
	Cell(int, int);

	// Accessors
	int getX();
	int getY();
	int getNeighbors();

	// Mutators
	void setX(int);
	void setY(int);
	void setNeighbors(int);

	// Methods
	void render();
	unsigned short countLiveNeighbors();
	unsigned short countDeadNeighbors();

	//Operators
	bool operator==(Cell);
	bool operator!=(Cell);
	bool operator>(Cell);
	bool operator>=(Cell);
	bool operator<(Cell);
	bool operator<=(Cell);
	Cell operator++();
	Cell operator++(int);
};