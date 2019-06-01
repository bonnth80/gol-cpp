#pragma once
#include <vector>
#include "cell.h"
#include "cellRenderer.h"
#include "golDebug.h"

class CensusManager {
private:
	std::vector<Cell> cellCensus_;
	std::vector<Cell> zygoteCensus_;
	Renderer renderer;
	int uiAreaHeight;
private:
	// Methods
	void swapCells(int, int);
	void swapZygotes(int, int);
	void sortCells();
	void sortZygotes();
	bool findCell(Cell);
	bool findCell(int, int);
	int addCell(Cell);
	void removeCell(Cell);

public:
	// Constructor
	CensusManager() {}

	CensusManager(std::vector<Cell> vC, HWND hwnd) {
		cellCensus_ = vC;
		sortCells();

		RECT rect;
		GetClientRect(hwnd, &rect);
		uiAreaHeight = 200;
		rect.bottom -= uiAreaHeight;

		RenderData rd;
		rd.cellSizeX = 10;
		rd.cellSizeY = 10;
		rd.originX = 0;
		rd.originY = 0;
		rd.clientArea = rect;

		rect.bottom -= uiAreaHeight;
		rd.renderArea = rect;
		renderer.setRenderData(rd);
	}

	// Methods
	void addCellXY(int, int);
	void removeCellXY(int, int);
	void setRenderArea(RECT);
	void renderState(HWND, HDC);

	void stepForward();
	void updateNeighborStatus(Cell &);
	void updateCellCensus();
};