#include "cellRow.h"


/************* Cell Row *********************/

// Constructor
CellRow::CellRow(int rowWidth, int colNum) {
	Cell *c;
	for (int i = 0; i < rowWidth; i++) {
		c = new Cell(i, colNum);
		cellRow_.push_back(c);
	}
}

// Destructor
CellRow::~CellRow() {
	for (unsigned int i = 0; i < cellRow_.size(); i++) {
		delete cellRow_[i];
	}
}

// Methods
Cell* CellRow::getCellAt(int position) {
	return cellRow_[position];
}

int CellRow::getRowSize() {
	return cellRow_.size();
}