#pragma once

class Cell {
private:
	int x;
	int y;
	bool isAlive;
	unsigned short liveAdj;
public:
	// constructor
	Cell(int, int, bool);

	// Accessors
	int getX();
	int getY();
	bool getAlive();

	// Mutators
	void setX(int);
	void setY(int);
	void setAlive(bool);

	// Methods
	void render();
	unsigned short countLiveNeighbors();
	unsigned short countDeadNeighbors();

	//Operators
	bool operator=(Cell);
	bool operator>(Cell);
	bool operator>=(Cell);
	bool operator<(Cell);
	bool operator<=(Cell);
};

class Zygote:Cell {
private:
public:
};