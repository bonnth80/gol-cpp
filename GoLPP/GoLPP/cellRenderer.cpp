#include "cellRenderer.h"
#include "cell.h"
#include <string>
#include "golDebug.h"

using namespace std;

void Renderer::drawGrid(HWND hwnd) {
	RECT rect;
	PAINTSTRUCT ps;
	HDC hdc;

	hdc = BeginPaint(hwnd, &ps);
	GetClientRect(hwnd, &rect);

	for (INT i = 0; i < rect.right; i += RenderData_.cellSizeX) {
		MoveToEx(hdc, i, 0, NULL);
		LineTo(hdc, i, rect.bottom);
	}

	for (INT i = 0; i < rect.bottom; i += RenderData_.cellSizeY) {
		MoveToEx(hdc, 0, i, NULL);
		LineTo(hdc, rect.right, i);
	}

#ifdef GOL_DEBUG_MODE
	INT sizeX = rect.right;
	WCHAR sizeXC[20];
	UINT bufferSizeX = wsprintf(sizeXC, TEXT("X size: %d"), sizeX);
	TextOut(hdc, 50, 50, sizeXC, bufferSizeX);

	INT sizeY = rect.bottom;
	WCHAR sizeYC[20];
	UINT bufferSizeY = wsprintf(sizeYC, TEXT("X size: %d"), sizeY);
	TextOut(hdc, 50, 80, sizeYC, bufferSizeY);
#endif

	EndPaint(hwnd, &ps);
}

void Renderer::drawCell(Cell cell) {

}