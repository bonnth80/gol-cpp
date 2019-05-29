#include "cellRenderer.h"
#include "cell.h"
#include <string>
#include "golDebug.h"

void Renderer::drawGrid(HWND hwnd, HDC hdc) {
	RECT rect;
	GetClientRect(hwnd, &rect);

	for (int i = 0; i < rect.right; i += render_data_.cellSizeX) {
		MoveToEx(hdc, i, 0, NULL);
		LineTo(hdc, i, rect.bottom);
	}

	for (int i = 0; i < rect.bottom; i += render_data_.cellSizeY) {
		MoveToEx(hdc, 0, i, NULL);
		LineTo(hdc, rect.right, i);
	}

}

void Renderer::drawCell(HWND hwnd, HDC hdc, Cell cell) {
	HBRUSH hBrush;

	hBrush = CreateSolidBrush(RGB(12,84,255));
	SelectObject(hdc, hBrush);

	Rectangle(hdc,
		render_data_.cellSizeX * cell.getX(),
		render_data_.cellSizeY * cell.getY(),
		render_data_.cellSizeX * (cell.getX() + 1) + 1,
		render_data_.cellSizeY * (cell.getY() + 1) + 1);

	DeleteObject(hBrush);
}

void Renderer::eraseCell(HWND hwnd, HDC hdc, Cell cell) {
	SelectObject(hdc, WHITE_BRUSH);

	Rectangle(hdc,
		render_data_.cellSizeX * cell.getX(),
		render_data_.cellSizeY * cell.getY(),
		render_data_.cellSizeX * (cell.getX() + 1) + 1,
		render_data_.cellSizeY * (cell.getY() + 1) + 1);
}

void Renderer::renderState(HWND hwnd, HDC hdc, std::vector<Cell> cellList) {
	for (unsigned int i = 0; i < cellList.size(); i++) {
			drawCell(hwnd, hdc, cellList[i]);
	}
}