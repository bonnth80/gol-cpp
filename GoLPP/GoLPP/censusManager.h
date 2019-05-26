#pragma once

#include <vector>
#include "cell.h"

class CensusManager {
private:
	std::vector<Cell> cellCensus_;
	std::vector<Zygote> zygoteCensus_;

public:
	void sortCells();
	void sortZygotes();
	void updateZygoteCensus();
	void stepForward();
};