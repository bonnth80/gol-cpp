#include <windows.h>
#include <vector>
#include <algorithm>
#include "censusController.h"
#include "cellRenderer.h"

/**********  Census Controller   ************/

// Constructor
CensusController::CensusController(int gridWidth, int gridHeight) {
	 GridWidth_ = gridWidth;
	 GridHeight_ = gridHeight;

	 // create cells
	 for (int i = 0; i < GridHeight_; i++) {		
		 CellGrid_.push_back(new CellRow(GridWidth_,i));
	 }

	 // configure cell neighborhoods
	 CellRow *cr;	// current cell Row
	 CellRow *crN;	// current Cell Row Neighbor reference
	 Cell *c;		// current cell
	 Cell *cN;		// current cell Neighbor reference

	 for (int y = 0; y < GridHeight_; y++) {
		 for (int x = 0; x < GridWidth_; x++) {

			 // NW Neighbor
			 if (x > 0 && y > 0) {
				 cr = CellGrid_[y];
				 c = cr->getCellAt(x);

				 crN = CellGrid_.at(y - 1);
				 cN = crN->getCellAt(x - 1);

				 c->setNeighbor(0, cN);
			 }

			 // N Neighbor
			 if (y > 0) {
				 cr = CellGrid_[y];
				 c = cr->getCellAt(x);

				 crN = CellGrid_.at(y - 1);
				 cN = crN->getCellAt(x);

				 c->setNeighbor(1, cN);
			 }

			 // NE Neighbor
			 if (x < GridWidth_ - 1 && y > 0) {
				 cr = CellGrid_[y];
				 c = cr->getCellAt(x);

				 crN = CellGrid_.at(y - 1);
				 cN = crN->getCellAt(x + 1);

				 c->setNeighbor(2, cN);
			 }

			 // W Neighbor
			 if (x > 0) {
				 cr = CellGrid_[y];
				 c = cr->getCellAt(x);

				 crN = CellGrid_.at(y);
				 cN = crN->getCellAt(x - 1);

				 c->setNeighbor(3, cN);
			 }

			 // E Neighbor
			 if (x < GridWidth_ - 1) {
				 cr = CellGrid_[y];
				 c = cr->getCellAt(x);

				 crN = CellGrid_.at(y);
				 cN = crN->getCellAt(x + 1);

				 c->setNeighbor(4, cN);
			 }

			 // SW Neighbor
			 if (x > 0 && y < GridHeight_ - 1) {
				 cr = CellGrid_[y];
				 c = cr->getCellAt(x);

				 crN = CellGrid_.at(y + 1);
				 cN = crN->getCellAt(x - 1);

				 c->setNeighbor(5, cN);
			 }

			 // S Neighbor
			 if (y < GridHeight_ - 1) {
				 cr = CellGrid_[y];
				 c = cr->getCellAt(x);

				 crN = CellGrid_.at(y + 1);
				 cN = crN->getCellAt(x);

				 c->setNeighbor(6, cN);
			 }

			 // SE Neighbor
			 if (x < GridWidth_ - 1 && y < GridHeight_ - 1) {
				 cr = CellGrid_[y];
				 c = cr->getCellAt(x);

				 crN = CellGrid_.at(y + 1);
				 cN = crN->getCellAt(x + 1);

				 c->setNeighbor(7, cN);
			 }
		 }
	 }
}

// Post Initialization
void CensusController::setData(RenderData rd) {
	r.setRenderData(rd);
}

// Methods
void CensusController::spawnCell(int x, int y) {
	CellGrid_[y]->getCellAt(x)->setIsAlive(true);
}

void CensusController::killCell(int x, int y) {
	CellGrid_[y]->getCellAt(x)->setIsAlive(false);
}

void CensusController::toggleCell(int x, int y) {
	CellGrid_[y]->getCellAt(x)->toggleIsAlive();
}

void CensusController::stepForward() {
	// Any live cell with fewer than two live neighbours dies, as if by underpopulation.
	// Any live cell with two or three live neighbours lives on to the next generation.
	// Any live cell with more than three live neighbours dies, as if by overpopulation.
	// Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

	std::vector<Cell *> toggleList;
	int nCounter = 0;

	Cell *c;
	for (int y = 0; y < GridHeight_; y++) {
		for (int x = 0; x < GridWidth_; x++) {
			nCounter = 0;
			c = CellGrid_[y]->getCellAt(x);

			for (int n = 0; n < 8; n++)
				nCounter += (c->getNeighbor(n) != nullptr && c->getNeighbor(n)->getIsAlive());

			if ((c->getIsAlive() && (nCounter < 2 || nCounter > 3))
				|| (!(c->getIsAlive()) && nCounter == 3))
					toggleList.push_back(c);
		}
	}

	for (unsigned int t = 0; t < toggleList.size(); t++) {
		toggleList[t]->toggleIsAlive();
	}
}

void CensusController::renderState(HWND hwnd, HDC hdc) {
	r.drawGrid(hwnd, hdc);
	r.renderState(hwnd, hdc, CellGrid_);

	// temp - render basic control help

	UINT buf = 0;
	WCHAR dbNfo[30];
	buf = wsprintf(dbNfo, TEXT("Mouse Left: Draw Cells"));
	TextOut(hdc, 40, 560, dbNfo, buf);
	buf = wsprintf(dbNfo, TEXT("Mouse Right: Erase Cells"));
	TextOut(hdc, 40, 580, dbNfo, buf);
	buf = wsprintf(dbNfo, TEXT("Any Key: Step Forward"));
	TextOut(hdc, 40, 600, dbNfo, buf);
	buf = wsprintf(dbNfo, TEXT("Hold Any Key: Play Forward"));
	TextOut(hdc, 40, 620, dbNfo, buf);
}