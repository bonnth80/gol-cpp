#pragma once

#include <vector>
#include "cell.h"
#include "cellRenderer.h"
#include "golDebug.h"

class CensusManager {
private:
	std::vector<Cell> cellCensus_;
	std::vector<Cell> zygoteCensus_;
	//std::vector<Cell> toggleList_;

private:
	// Methods
	void swapCells(int, int);
	void swapZygotes(int, int);
	void sortCells();
	int addCell(Cell);
	void sortZygotes();
	bool findCell(Cell);
	bool findCell(int, int);

public:
	// Constructor
	CensusManager() {}
	CensusManager(std::vector<Cell> vC) {
		cellCensus_ = vC;
		sortCells();
	}

	// Methods
	void renderState(HWND, HDC, Renderer);

	void stepForward();
	void updateNeighborStatus(Cell &);
	void updateCellCensus();
	//void processToggleList();
};