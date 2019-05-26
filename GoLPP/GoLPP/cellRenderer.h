#pragma once
#include "cell.h"
#include <windows.h>
#include <vector>

struct RenderData {
	int cellSizeX;
	int cellSizeY;
	int sizeX;
	int sizeY;
	int originX;
	int originY;
	
};

class Renderer {
private:
	std::vector<Cell> cell_data_;
	RenderData RenderData_;
public:
	Renderer() {
		RenderData_.cellSizeX = 10;
		RenderData_.cellSizeY = 10;
		RenderData_.sizeX = 50;
		RenderData_.sizeY = 50;
		RenderData_.originX = 0;
		RenderData_.originY = 0;
	}

	Renderer(int cX, int cY, int sX, int sY, int oX, int oY) {
		RenderData_.cellSizeX = cX;
		RenderData_.cellSizeY = cY;
		RenderData_.sizeX = sX;
		RenderData_.sizeY = sY;
		RenderData_.originX = oX;
		RenderData_.originY = oY;
	}

	// Mutator
	void setRenderData();
	void setCellData(std::vector<Cell>);

	// Methods
	void drawGrid(HWND);
	void drawCell(Cell);
	void eraseCell(Cell);
	void renderState(HWND);
};