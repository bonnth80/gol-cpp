#pragma once

class cell {
private:
	int x;
	int y;
	bool isAlive;
	unsigned short liveAdj;
public:
	// constructor
	cell(int, int, bool);

	// Methods
	void render();
	unsigned short countLiveNeighbors();
	unsigned short countDeadNeighbors();
};

class zygote:cell {
private:
public:
};