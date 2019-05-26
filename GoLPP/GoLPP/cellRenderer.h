#pragma once
#include "cell.h"
#include <windows.h>
#include <vector>

struct renderData {
	int cellSizeX;
	int cellSizeY;
	int sizeX;
	int sizeY;
	int originX;
	int originY;
	
};

class renderer {
private:
	std::vector<cell> cellData;
	renderData rd;
public:
	renderer() {
		rd.cellSizeX = 10;
		rd.cellSizeY = 10;
		rd.sizeX = 50;
		rd.sizeY = 50;
		rd.originX = 0;
		rd.originY = 0;
	}

	renderer(int cX, int cY, int sX, int sY, int oX, int oY) {
		rd.cellSizeX = cX;
		rd.cellSizeY = cY;
		rd.sizeX = sX;
		rd.sizeY = sY;
		rd.originX = oX;
		rd.originY = oY;
	}

	// Mutator
	void setRenderData();
	void setCellData(std::vector<cell>);

	// Methods
	void drawGrid(HWND);
	void drawCell(int x, int y);
	void eraseCell(int x, int y);
	void renderState(HWND);
};