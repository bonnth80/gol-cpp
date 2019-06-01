#pragma once
#include "cell.h"
#include <windows.h>
#include <vector>

struct RenderData {
	int cellSizeX;		// horizontal size of cells in pixels
	int cellSizeY;		// vertical size of cells in pixels
	int originX;		// pixel location of x origin
	int originY;		// pixel location of y origin
	RECT clientArea;	// Are of client	
	RECT renderArea;	// Area of client to draw grid
};

class Renderer {
private:
	RenderData render_data_;
public:
	// Constructor
	Renderer() {
		render_data_.cellSizeX = 10;
		render_data_.cellSizeY = 10;
		render_data_.originX = 0;
		render_data_.originY = 0;
	}

	Renderer(RenderData rd) {
		render_data_ = rd;
	}

	// Accessors
	RenderData getRenderData();

	// Mutators
	void setRenderData(RenderData rd) { render_data_ = rd; };
	void setClientArea(RECT);
	void setRenderArea(RECT);

	// Methods
	void drawGrid(HWND, HDC);
	void drawCell(HWND, HDC, Cell);
	void renderState(HWND, HDC, std::vector<Cell>);
};