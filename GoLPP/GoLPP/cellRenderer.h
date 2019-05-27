#pragma once
#include "cell.h"
#include <windows.h>
#include <vector>

struct RenderData {
	INT cellSizeX;		// horizontal size of cells in pixels
	INT cellSizeY;		// vertical size of cells in pixels
	INT originX;		// pixel location of x origin
	INT originY;		// pixel location of y origin
	
};

class Renderer {
private:
	std::vector<Cell> cell_data_;
	RenderData render_data_;
public:
	// Constructor
	Renderer() {
		render_data_.cellSizeX = 10;
		render_data_.cellSizeY = 10;
		render_data_.originX = 0;
		render_data_.originY = 0;
	}

	Renderer(INT cX, INT cY, INT oX, INT oY) {
		render_data_.cellSizeX = cX;
		render_data_.cellSizeY = cY;
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