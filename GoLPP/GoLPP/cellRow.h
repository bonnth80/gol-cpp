#pragma once
#include <vector>
#include "cell.h"
/*************** CELL ROW ***********************/
class CellRow {
private:
	std::vector<Cell *> cellRow_;
public:
	// Constructor
	CellRow(int, int);

	// Destructor
	~CellRow();

	//Methods
	Cell* getCellAt(int position);
	int getRowSize();
};