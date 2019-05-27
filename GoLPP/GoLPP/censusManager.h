#pragma once

#include <vector>
#include "cell.h"
#include "cellRenderer.h"
#include "golDebug.h"

class CensusManager {
private:
	std::vector<Cell> cellCensus_;
	std::vector<Cell> zygoteCensus_;

private:
	// Methods
	void swapCells(int, int);
	void swapZygotes(int, int);

public:
	// Constructor
	CensusManager() {}
	CensusManager(std::vector<Cell> vC) {
		cellCensus_ = vC;
		sortCells();
	}

	// Methods
	void renderState(HWND, HDC, Renderer);

	void sortCells();
	int addCell(Cell);
	void sortZygotes();
	void addZygote(Cell);


	void updateZygoteCensus();

	void stepForward();
};