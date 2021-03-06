// Windows API Boilerplate

#include <windows.h>
#include <vector>
#include "cell.h"
#include "censusController.h"
#include "cellRenderer.h"
#include "golDebug.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow) {
	static TCHAR szAppName[] = TEXT("Boilerplate");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass)) {
		MessageBox(NULL, TEXT("Failed to register window class."),
			szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName, TEXT("Boilerplate"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

void GetLargestDisplayMode(int * pcxBitmap, int * pcyBitmap)
{
	DEVMODE devmode;
	int     iModeNum = 0;

	*pcxBitmap = *pcyBitmap = 0;

	ZeroMemory(&devmode, sizeof(DEVMODE));
	devmode.dmSize = sizeof(DEVMODE);

	while (EnumDisplaySettings(NULL, iModeNum++, &devmode))
	{
		*pcxBitmap = max(*pcxBitmap, (int)devmode.dmPelsWidth);
		*pcyBitmap = max(*pcyBitmap, (int)devmode.dmPelsHeight);
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	static HDC hdcShadowMem = 0;
	static RECT rect, renderRect;
	static HBITMAP hBitmap;

	static int cxBitmap, cyBitmap, cxClient,cyClient;
	static bool lMouseDown = false, rMouseDown = false;
	INT mouseX = 0, mouseY = 0;

	RenderData rd;

	static CensusController GoL(200,100);

	// **********  MESSAGE HANDLING ******************
	switch (message) {
	case WM_CREATE:
		GetLargestDisplayMode(&cxBitmap, &cyBitmap);
		GetClientRect(hwnd, &rect);

		rd.cellSizeX = 10;
		rd.cellSizeY = 10;
		rd.clientArea = rect;
		rd.originX = 0;
		rd.originY = 0;
		rd.renderArea = rect;
		rd.renderArea.bottom -= 200;

		GoL.setData(rd);

		hdc = GetDC(hwnd);
		hBitmap = CreateCompatibleBitmap(hdc, cxBitmap, cyBitmap);
		hdcShadowMem = CreateCompatibleDC(hdc);
		ReleaseDC(hwnd, hdc);

		if (!hBitmap)       // no memory for bitmap
		{
			DeleteDC(hdcShadowMem);
			return -1;
		}

		SelectObject(hdcShadowMem, hBitmap);
		PatBlt(hdcShadowMem, 0, 0, cxBitmap, cyBitmap, WHITENESS);
		return 0;

	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);

		rd.cellSizeX = 10;
		rd.cellSizeY = 10;
		rd.clientArea = rect;
		rd.originX = 0;
		rd.originY = 0;
		rd.renderArea = rect;
		rd.renderArea.bottom -= 200;

		GoL.setData(rd);
		return 0;

	case WM_ERASEBKGND:
		return 1;

	case WM_PAINT:		
		GoL.renderState(hwnd,hdcShadowMem);

		hdc = BeginPaint(hwnd, &ps);

		BitBlt(hdc, 0, 0, cxClient, cyClient, hdcShadowMem, 0, 0, SRCCOPY);
		
		EndPaint(hwnd, &ps);
		return 0;

	case WM_KEYDOWN:
		GoL.stepForward();

		InvalidateRect(hwnd, NULL, TRUE);
		return 0;

	case WM_LBUTTONDOWN:
		mouseX = LOWORD(lParam);
		mouseY = HIWORD(lParam);
		lMouseDown = true;
		GoL.spawnCell(int(mouseX / 10), int(mouseY / 10));

		InvalidateRect(hwnd, NULL, TRUE);
		return 0;

	case WM_LBUTTONUP:
		lMouseDown = false;
		return 0;

	case WM_RBUTTONDOWN:
		mouseX = LOWORD(lParam);
		mouseY = HIWORD(lParam);
		rMouseDown = true;
		GoL.killCell(int(mouseX / 10), int(mouseY / 10));

		InvalidateRect(hwnd, NULL, TRUE);
		return 0;

	case WM_RBUTTONUP:
		rMouseDown = false;
		return 0;

	case WM_MOUSEMOVE:
		mouseX = LOWORD(lParam);
		mouseY = HIWORD(lParam);
		if (lMouseDown) {
			GoL.spawnCell(int(mouseX / 10), int(mouseY / 10));

			InvalidateRect(hwnd, NULL, TRUE);
			return 0;
		}

		if (rMouseDown) {
			GoL.killCell(int(mouseX / 10), int(mouseY / 10));

			InvalidateRect(hwnd, NULL, TRUE);
			return 0;
		}

		return 0;

	case WM_DESTROY:
		DeleteDC(hdcShadowMem);
		DeleteObject(hBitmap);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}