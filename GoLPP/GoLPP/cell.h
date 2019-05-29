#pragma once

class Cell {
private:
	int x;
	int y;
	bool isAlive;
	int neighbors;
public:
	// constructor
	Cell() {
		x = 0;
		y = 0;
		isAlive = true;
		neighbors = 0;
	}
	Cell(int, int, bool);

	// Accessors
	int getX();
	int getY();
	bool getAlive();
	int getNeighbors();

	// Mutators
	void setX(int);
	void setY(int);
	void setAlive(bool);
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