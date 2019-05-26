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
	CensusManager() {
#ifdef GOL_DEBUG_MODE
		static Cell cell_00(5, 3, true), cell_01(43, 44, true), cell_02(45, 43, true);
		cellCensus_.push_back(cell_00);
		cellCensus_.push_back(cell_01);
		cellCensus_.push_back(cell_02);
#endif
	}

	void renderState(HWND, HDC, Renderer);
	void sortCells();
	void sortZygotes();
	void updateZygoteCensus();
	void stepForward();
};