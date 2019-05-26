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

	// Methods
	void render();
	unsigned short countLiveNeighbors();
	unsigned short countDeadNeighbors();
};

class Zygote:Cell {
private:
public:
};