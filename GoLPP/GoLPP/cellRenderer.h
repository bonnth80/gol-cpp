#pragma once
#include "cell.h"
#include "cellRow.h"
#include "renderData.h"
#include <windows.h>
#include <vector>

class GOL_Renderer {
private:
	RenderData render_data_;
public:
	// Constructor
	GOL_Renderer() {
		render_data_.cellSizeX = 10;
		render_data_.cellSizeY = 10;
		render_data_.originX = 0;
		render_data_.originY = 0;
	}

	GOL_Renderer(RenderData rd) {
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
	void renderState(HWND, HDC, std::vector<CellRow *>);
};