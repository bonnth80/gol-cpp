#include "cellRenderer.h"
#include "cell.h"
#include <string>
#include "golDebug.h"

void Renderer::drawGrid(HWND hwnd, HDC hdc) {
	HBRUSH hBrush;

	hBrush = CreateSolidBrush(RGB(255,255,255));
	SelectObject(hdc, hBrush);

	Rectangle(hdc,0,0,render_data_.clientArea.right, render_data_.clientArea.bottom);

	ReleaseDC(hwnd, hdc);
	DeleteObject(hBrush);

	for (int i = 0; i <= render_data_.renderArea.right; i += render_data_.cellSizeX) {
		MoveToEx(hdc, i, 0, NULL);
		LineTo(hdc, i, render_data_.renderArea.bottom);
	}

	for (int i = 0; i <= render_data_.renderArea.bottom; i += render_data_.cellSizeY) {
		MoveToEx(hdc, 0, i, NULL);
		LineTo(hdc, render_data_.renderArea.right, i);
	}
}

void Renderer::drawCell(HWND hwnd, HDC hdc, Cell cell) {
	HBRUSH hBrush;

	hBrush = CreateSolidBrush(RGB(36,68,149));
	SelectObject(hdc, hBrush);

	Rectangle(hdc,
		render_data_.cellSizeX * cell.getX(),
		render_data_.cellSizeY * cell.getY(),
		render_data_.cellSizeX * (cell.getX() + 1) + 1,
		render_data_.cellSizeY * (cell.getY() + 1) + 1);

	ReleaseDC(hwnd, hdc);
	DeleteObject(hBrush);
}

void Renderer::renderState(HWND hwnd, HDC hdc, std::vector<Cell> cellList) {
	for (unsigned int i = 0; i < cellList.size(); i++) {
		if (cellList[i].getX() * render_data_.cellSizeX > render_data_.renderArea.left
			&& cellList[i].getX() * render_data_.cellSizeX < render_data_.renderArea.right
			&& cellList[i].getY() * render_data_.cellSizeY > render_data_.renderArea.top
			&& cellList[i].getY() * render_data_.cellSizeY < render_data_.renderArea.bottom)
			drawCell(hwnd, hdc, cellList[i]);
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