#include <vector>
#include <windows.h>
#include "censusManager.h"
#include "cellRenderer.h"

void CensusManager::renderState(HWND hwnd, HDC hdc, Renderer r) {
	r.drawGrid(hwnd, hdc);
	r.renderState(hwnd, hdc, cellCensus_);
}