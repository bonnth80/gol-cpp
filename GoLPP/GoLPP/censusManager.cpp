#include <windows.h>
#include <vector>
#include <algorithm>
#include "censusManager.h"
#include "cellRenderer.h"

/*************** Configuration ****************/
void CensusManager::setRenderArea(RECT rect) {
	rect.bottom -= uiAreaHeight;
	renderer.setRenderArea(rect);
}

/***************** Private Methods *****************/
void CensusManager::renderState(HWND hwnd, HDC hdc) {
	RECT rect;
	GetClientRect(hwnd, &rect);

	setRenderArea(rect);
	renderer.drawGrid(hwnd, hdc);


	renderer.renderState(hwnd, hdc, cellCensus_);
}

void CensusManager::swapCells(int a, int b) {
	Cell temp = cellCensus_[a];
	cellCensus_[a] = cellCensus_[b];
	cellCensus_[b] = temp;
}
void CensusManager::swapZygotes(int a, int b) {
	Cell temp = zygoteCensus_[a];
	zygoteCensus_[a] = zygoteCensus_[b];
	zygoteCensus_[b] = temp;
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

void CensusManager::sortZygotes() {
	// Selection sort
	INT minElement = 0;

	for (int i = 0; i < zygoteCensus_.size() - 1; i++) {
		minElement = i;

		for (int j = i + 1; j < zygoteCensus_.size(); j++)
			if (zygoteCensus_[j] < zygoteCensus_[minElement])
				minElement = j;

		if (i != minElement)
			swapZygotes(i, minElement);
	}
}

int CensusManager::addCell(Cell c) {
	// if c is lower than the first element,
	// just insert at 0
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

	if (low == high)
		return cellCensus_[low] == c;

	return false;
}

bool CensusManager::findCell(int x, int y) {
	Cell newCell(x, y, true);
	return findCell(newCell);
}

/******************* GOL LOGIC **************************/

void CensusManager::stepForward() {
	zygoteCensus_.clear();

	for (int i = 0; i < cellCensus_.size(); i++)
		updateNeighborStatus(cellCensus_[i]);

	sortZygotes();
	updateCellCensus();
}

void CensusManager::updateNeighborStatus(Cell &c) {
	c.setNeighbors(0);
	
	if (findCell(c.getX() - 1, c.getY() - 1)) c.setNeighbors(c.getNeighbors() + 1);// c++;
	else zygoteCensus_.push_back(*(new Cell(c.getX() - 1, c.getY() - 1, true)));

	if (findCell(c.getX(), c.getY() - 1)) c.setNeighbors(c.getNeighbors() + 1);//c++;
	else zygoteCensus_.push_back(*(new Cell(c.getX(), c.getY() - 1, true)));

	if (findCell(c.getX() + 1, c.getY() - 1)) c.setNeighbors(c.getNeighbors() + 1);//c++;
	else zygoteCensus_.push_back(*(new Cell(c.getX() + 1, c.getY() - 1, true)));

	if (findCell(c.getX() - 1, c.getY())) c.setNeighbors(c.getNeighbors() + 1);//c++;
	else zygoteCensus_.push_back(*(new Cell(c.getX() - 1, c.getY(), true)));

	if (findCell(c.getX() + 1, c.getY())) c.setNeighbors(c.getNeighbors() + 1);//c++;
	else zygoteCensus_.push_back(*(new Cell(c.getX() + 1, c.getY(), true)));

	if (findCell(c.getX() - 1, c.getY() + 1)) c.setNeighbors(c.getNeighbors() + 1);//c++;
	else zygoteCensus_.push_back(*(new Cell(c.getX() - 1, c.getY() + 1, true)));

	if (findCell(c.getX(), c.getY() + 1)) c.setNeighbors(c.getNeighbors() + 1);//c++;
	else zygoteCensus_.push_back(*(new Cell(c.getX(), c.getY() + 1, true)));

	if (findCell(c.getX() + 1, c.getY() + 1)) c.setNeighbors(c.getNeighbors() + 1);//c++;
	else zygoteCensus_.push_back(*(new Cell(c.getX() + 1, c.getY() + 1, true)));
}

void CensusManager::updateCellCensus() {
	for (int i = cellCensus_.size() - 1; i >= 0; i--)
		if (cellCensus_[i].getNeighbors() < 2 || cellCensus_[i].getNeighbors() > 3)
			cellCensus_.erase(cellCensus_.begin() + i);

	// trim zygote census
	int currentCtr = 1;
	for (int i = 1; i < zygoteCensus_.size(); i++) {
		if (zygoteCensus_[i - 1] == zygoteCensus_[i]) {
			currentCtr++;
		} else {
			if (currentCtr == 3) {	// If live neighbor count is exactly 3
				addCell(zygoteCensus_[i-1]);
			}
			currentCtr = 1;
		}
	}
}