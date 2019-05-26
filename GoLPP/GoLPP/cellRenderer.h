#pragma once
#include "cell.h"
#include <windows.h>
#include <vector>

struct RenderData {
	INT cellSizeX;
	INT cellSizeY;
	INT sizeX;
	INT sizeY;
	INT originX;
	INT originY;
	
};

class Renderer {
private:
	std::vector<Cell> cell_data_;
	RenderData render_data_;
public:
	Renderer() {
		render_data_.cellSizeX = 10;
		render_data_.cellSizeY = 10;
		render_data_.sizeX = 50;
		render_data_.sizeY = 50;
		render_data_.originX = 0;
		render_data_.originY = 0;
	}

	Renderer(INT cX, INT cY, INT sX, INT sY, INT oX, INT oY) {
		render_data_.cellSizeX = cX;
		render_data_.cellSizeY = cY;
		render_data_.sizeX = sX;
		render_data_.sizeY = sY;
		render_data_.originX = oX;
		render_data_.originY = oY;
	}

	// Mutator
	void setRenderData();
	void setCellData(std::vector<Cell>);

	// Methods
	void drawGrid(HWND, HDC);
	void drawCell(HWND, HDC, Cell);
	void eraseCell(HWND, HDC, Cell);
	void renderState(HWND, HDC, std::vector<Cell>);
};