#pragma once
#include "windows.h"

struct RenderData {
	int cellSizeX;		// horizontal size of cells in pixels
	int cellSizeY;		// vertical size of cells in pixels
	int originX;		// pixel location of x origin
	int originY;		// pixel location of y origin
	RECT clientArea;	// Are of client	
	RECT renderArea;	// Area of client to draw grid
};