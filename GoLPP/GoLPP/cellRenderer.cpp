#include "cellRenderer.h"
#include "cell.h"
#include <string>
#include "golDebug.h"

void Renderer::drawGrid(HWND hwnd, HDC hdc) {
	RECT rect;
	GetClientRect(hwnd, &rect);

	for (INT i = 0; i < rect.right; i += render_data_.cellSizeX) {
		MoveToEx(hdc, i, 0, NULL);
		LineTo(hdc, i, rect.bottom);
	}

	for (INT i = 0; i < rect.bottom; i += render_data_.cellSizeY) {
		MoveToEx(hdc, 0, i, NULL);
		LineTo(hdc, rect.right, i);
	}

#ifdef GOL_DEBUG_MODE
	INT sizeX = rect.right;
	WCHAR sizeXC[20];
	UINT bufferSizeX = wsprintf(sizeXC, TEXT("X size: %d"), sizeX);
	TextOut(hdc, 200, 100, sizeXC, bufferSizeX);

	INT sizeY = rect.bottom;
	WCHAR sizeYC[20];
	UINT bufferSizeY = wsprintf(sizeYC, TEXT("X size: %d"), sizeY);
	TextOut(hdc, 200, 180, sizeYC, bufferSizeY);
#endif
}

void Renderer::drawCell(HWND hwnd, HDC hdc, Cell cell) {
	HBRUSH hBrush;

	hBrush = CreateSolidBrush(RGB(12,84,255));
	SelectObject(hdc, hBrush);

#ifdef GOL_DEBUG_MODE
	INT rectX1 = render_data_.cellSizeX * cell.getX();
	WCHAR rectX1C[20];
	UINT bufferRectX1 = wsprintf(rectX1C, TEXT("X1: %d"), rectX1);
	TextOut(hdc, 400, 80, rectX1C, bufferRectX1);

	INT rectY1 = render_data_.cellSizeY * cell.getY();
	WCHAR rectY1C[20];
	UINT bufferRectY1 = wsprintf(rectY1C, TEXT("Y1: %d"), rectY1);
	TextOut(hdc, 400, 100, rectY1C, bufferRectY1);

	INT rectX2 = render_data_.cellSizeX * cell.getX();
	WCHAR rectX2C[20];
	UINT bufferRectX2 = wsprintf(rectX1C, TEXT("X2: %d"), rectX2);
	TextOut(hdc, 400, 120, rectX1C, bufferRectX1);

	INT rectY2 = render_data_.cellSizeY * cell.getY();
	WCHAR rectY2C[20];
	UINT bufferRectY2 = wsprintf(rectY2C, TEXT("Y2: %d"), rectY2);
	TextOut(hdc, 400, 100, rectY2C, bufferRectY2);
#endif

	Rectangle(hdc,
		render_data_.cellSizeX * cell.getX(),
		render_data_.cellSizeY * cell.getY(),
		render_data_.cellSizeX * (cell.getX() + 1),
		render_data_.cellSizeY * (cell.getY() + 1));

	DeleteObject(hBrush);
}

void Renderer::eraseCell(HWND hwnd, HDC hdc, Cell cell) {
	SelectObject(hdc, WHITE_BRUSH);

	Rectangle(hdc,
		render_data_.cellSizeX * cell.getX(),
		render_data_.cellSizeY * cell.getY(),
		render_data_.cellSizeX * (cell.getX() + 1),
		render_data_.cellSizeY * (cell.getY() + 1));
}

void Renderer::renderState(HWND hwnd, HDC hdc, std::vector<Cell> cellList) {
	for (INT i = 0; i < cellList.size(); i++) {
		if (cellList[i].getAlive())
			drawCell(hwnd, hdc, cellList[i]);
		else
			eraseCell(hwnd, hdc, cellList[i]);
	}
}