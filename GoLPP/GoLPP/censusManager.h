#pragma once

#include <vector>
#include "cell.h"

class censusManager {
private:
	std::vector<cell> cellCensus;
	std::vector<zygote> zygoteCensus;

public:
	void sortCells();
	void sortZygotes();
	void updateZygoteCensus();
	void stepForward();
};