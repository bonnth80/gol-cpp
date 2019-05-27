#include <vector>
#include <windows.h>
#include "censusManager.h"
#include "cellRenderer.h"

void CensusManager::swapCells(int a, int b) {
	Cell temp = cellCensus_[a];
	cellCensus_[a] = cellCensus_[b];
	cellCensus_[b] = temp;
}

void CensusManager::renderState(HWND hwnd, HDC hdc, Renderer r) {
	r.drawGrid(hwnd, hdc);
	r.renderState(hwnd, hdc, cellCensus_);
}

void CensusManager::sortCells() {
	// Selection sort
	INT minElement = 0;

	for (int i = 0; i < cellCensus_.size() - 1; i++) {
		minElement = i;

		for (int j = i + 1; j < cellCensus_.size(); j++)
			if (cellCensus_[j] < cellCensus_[minElement])
				minElement = j;

		if (i != minElement)
			swapCells(i, minElement);
	}
}

int CensusManager::addCell(Cell c) {
	// if c is lower than the first element, just
	// insert at 0
	if (c < cellCensus_[0]) {
		cellCensus_.insert(cellCensus_.begin(), c);
		return 0;
	}	

	int ctr = 1;
	std::vector<Cell>::iterator cit = cellCensus_.begin();

	// find element index to insert cell into and insert it
	do {
		ctr++;
		if (c > *cit && ++cit != cellCensus_.end() && c < *cit) {
			cellCensus_.insert(cit, c);
			return ctr;
		}
	} while (cit != cellCensus_.end());

	// if c is greater than all the elements, insert cell
	// into last index
	cellCensus_.push_back(c);
	return cellCensus_.size();
}

void CensusManager::sortZygotes() {
	//stub
}

int CensusManager::addZygote(Cell c) {
	//stub
	return 0;
}

bool CensusManager::findCell(Cell c) {
	int low = 0,
		mid = 0,
		high = cellCensus_.size() - 1;


	while (low < high) {
		mid = low + (high - low) / 2;
		if (cellCensus_[mid] == c)
			return true;

		if (cellCensus_[mid] < c)
			low = mid + 1;

		else
			high = mid - 1;
	}

	return false;
}

void CensusManager::updateZygoteCensus() {
	//stub
}

void CensusManager::stepForward() {

}