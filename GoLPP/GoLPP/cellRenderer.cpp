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

#ifdef GOL_DEBUG_MODE
	INT sizeX = rect.right;
	WCHAR sizeXC[20];
	UINT bufferSizeX = wsprintf(sizeXC, TEXT("X size: %d"), sizeX);
	TextOut(hdc, GDC.getLeft(), GDC.useLine(), sizeXC, bufferSizeX);

	INT sizeY = rect.bottom;
	WCHAR sizeYC[20];
	UINT bufferSizeY = wsprintf(sizeYC, TEXT("X size: %d"), sizeY);
	TextOut(hdc, GDC.getLeft(), GDC.useLine(), sizeYC, bufferSizeY);
#endif
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
		if (cellList[i].getAlive())
			drawCell(hwnd, hdc, cellList[i]);
		else
			eraseCell(hwnd, hdc, cellList[i]);
	}

#ifdef GOL_DEBUG_MODE
	for (unsigned int i = 0; i < cellList.size(); i++) {
		INT cellX = cellList[i].getX();
		INT cellY = cellList[i].getY();
		WCHAR cellInfo[24];
		UINT bufferRectX1 = wsprintf(cellInfo, TEXT("Cell %d: (%d,%d)"), i, cellX, cellY);
		TextOut(hdc, GDC.getLeft(), GDC.useLine(), cellInfo, bufferRectX1);
	}
#endif
}