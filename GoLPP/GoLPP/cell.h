#pragma once

/*
Cell Neighborhood

-------------------------
|       |       |       |
|   0   |   1   |   2   |
|       |       |       |
-------------------------
|       | \   / |       |
|   3   |   C   |   4   |
|       | /   \ |       |
-------------------------
|       |       |       |
|   5   |   6   |   7   |
|       |       |       |
-------------------------

*/

class Cell {
private:
	int x;
	int y;
	bool isAlive;
	Cell *neighborhood[8];
public:
	// constructor
	Cell() {
		x = 0;
		y = 0;
		isAlive = false;
	}

	Cell(int, int);

	// Accessors
	int getX();
	int getY();
	bool getIsAlive();
	Cell *getNeighbor(int);

	// Mutators
	void setNeighbor(int, Cell *);
	void toggleIsAlive();
	void setIsAlive(bool);

	//// Methods
	//void render();
	//unsigned short countLiveNeighbors();
	//unsigned short countDeadNeighbors();

	////Operators
	//bool operator==(Cell);
	//bool operator!=(Cell);
	//bool operator>(Cell);
	//bool operator>=(Cell);
	//bool operator<(Cell);
	//bool operator<=(Cell);
	//Cell operator++();
	//Cell operator++(int);
};