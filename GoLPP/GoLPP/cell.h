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

	// Mutators
	int getX();
	int getY();

	// Accessors
	void setX();
	void setY();

	// Methods
	void render();
	unsigned short countLiveNeighbors();
	unsigned short countDeadNeighbors();
};

class Zygote:Cell {
private:
public:
};