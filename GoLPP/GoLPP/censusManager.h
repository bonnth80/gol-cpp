#pragma once

#include <vector>
#include "cell.h"
#include "cellRenderer.h"
#include "golDebug.h"

class CensusManager {
private:
	std::vector<Cell> cellCensus_;
	std::vector<Zygote> zygoteCensus_;

public:
	// Constructor
	CensusManager() {}
	CensusManager(std::vector<Cell> vC) {cellCensus_ = vC;}

	void renderState(HWND, HDC, Renderer);
	void sortCells();
	void sortZygotes();
	void updateZygoteCensus();
	void stepForward();
};