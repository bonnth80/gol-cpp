#include "cellRenderer.h"
#include "cell.h"
#include <string>
#include "golDebug.h"

void Renderer::drawGrid(HWND hwnd, HDC hdcM) {
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

void Renderer::drawCell(HWND hwnd, HDC hdcM, Cell cell) {
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

void Renderer::renderState(HWND hwnd, HDC hdcM, std::vector<Cell> cellList) {
	for (unsigned int i = 0; i < cellList.size(); i++) {
		if (cellList[i].getX() * render_data_.cellSizeX > render_data_.renderArea.left
			&& cellList[i].getX() * render_data_.cellSizeX < render_data_.renderArea.right
			&& cellList[i].getY() * render_data_.cellSizeY > render_data_.renderArea.top
			&& cellList[i].getY() * render_data_.cellSizeY < render_data_.renderArea.bottom)
			drawCell(hwnd, hdcM, cellList[i]);
	}
}

RenderData Renderer::getRenderData() {
	return render_data_;
}

void Renderer::setClientArea(RECT rect) {
	render_data_.clientArea = rect;
}

void Renderer::setRenderArea(RECT rect) {
	render_data_.renderArea = rect;
}