#pragma once
#include <vector>
#include "cell.h"
#include "cellRow.h"
#include "cellRenderer.h"
#include "golDebug.h"

/**************** CENSUS CONTROLLER *********************/
class CensusController {
private:
	std::vector<CellRow *> CellGrid_;
	int GridWidth_;
	int GridHeight_;
	GOL_Renderer r;

public:
	// Constructor
	CensusController(int, int);

	// Destructor
	~CensusController() {
		for (unsigned int i = 0; i < CellGrid_.size(); i++) {
			delete CellGrid_[i];
		}
	}

	// Post Initialization
	void setData(RenderData);

	// Methods - Game Logic
	void stepForward();
	void renderState(HWND, HDC);
	void toggleCell(int, int);
	void spawnCell(int, int);
	void killCell(int, int);
};