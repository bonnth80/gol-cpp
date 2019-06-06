#include "cellRenderer.h"
#include "cell.h"
#include "censusController.h"
#include "cellRow.h"
#include <string>
#include "golDebug.h"

void GOL_Renderer::drawGrid(HWND hwnd, HDC hdcM) {
	HBRUSH hBrush;

	hBrush = CreateSolidBrush(RGB(255,255,255));
	SelectObject(hdcM, hBrush);

	Rectangle(hdcM,0,0,render_data_.clientArea.right, render_data_.clientArea.bottom);

	ReleaseDC(hwnd, hdcM);
	DeleteObject(hBrush);

	for (int i = 0; i <= render_data_.renderArea.right; i += render_data_.cellSizeX) {
		MoveToEx(hdcM, i, 0, NULL);
		LineTo(hdcM, i, render_data_.renderArea.bottom);
	}

	for (int i = 0; i <= render_data_.renderArea.bottom; i += render_data_.cellSizeY) {
		MoveToEx(hdcM, 0, i, NULL);
		LineTo(hdcM, render_data_.renderArea.right, i);
	}
}

void GOL_Renderer::drawCell(HWND hwnd, HDC hdcM, Cell cell) {
	HBRUSH hBrush;

	hBrush = CreateSolidBrush(RGB(36,68,149));
	SelectObject(hdcM, hBrush);

	Rectangle(hdcM,
		render_data_.cellSizeX * cell.getX(),
		render_data_.cellSizeY * cell.getY(),
		render_data_.cellSizeX * (cell.getX() + 1) + 1,
		render_data_.cellSizeY * (cell.getY() + 1) + 1);

	ReleaseDC(hwnd, hdcM);
	DeleteObject(hBrush);
}

void GOL_Renderer::renderState(HWND hwnd, HDC hdcM, std::vector<CellRow *> cellGrid) {
	Cell *c;
	for (unsigned int y = 0; y < cellGrid.size(); y++) {
		for (unsigned int x = 0; x < cellGrid[y]->getRowSize(); x++) {
			c = cellGrid[y]->getCellAt(x);

			if (c->getIsAlive()) {

				if (c->getX() * render_data_.cellSizeX > render_data_.renderArea.left
					&& c->getX() * render_data_.cellSizeX < render_data_.renderArea.right
					&& c->getY() * render_data_.cellSizeY > render_data_.renderArea.top
					&& c->getY() * render_data_.cellSizeY < render_data_.renderArea.bottom)

					drawCell(hwnd, hdcM, *c);

			}
		}
	}
}

RenderData GOL_Renderer::getRenderData() {
	return render_data_;
}

void GOL_Renderer::setClientArea(RECT rect) {
	render_data_.clientArea = rect;
}

void GOL_Renderer::setRenderArea(RECT rect) {
	render_data_.renderArea = rect;
}