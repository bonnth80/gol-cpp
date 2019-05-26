#include "cell.h"

cell::cell(int px, int py, bool pb) {
	x = px;
	y = py;
	isAlive = pb;
	liveAdj = 0;
}