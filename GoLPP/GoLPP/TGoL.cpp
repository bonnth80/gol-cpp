// Windows API Boilerplate

#include <windows.h>
#include <vector>
#include "cell.h"
#include "censusManager.h"
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

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;


#ifdef GOL_DEBUG_MODE
	GDC.resetCurrentLine();

	static Cell cell_00(20, 20, true),
			cell_01(21, 21, true),
			cell_02(22, 21, true),
			cell_03(22, 20, true),
			cell_04(22, 19, true);
	static std::vector<Cell> vC;
	vC.push_back(cell_00);
	vC.push_back(cell_01);
	vC.push_back(cell_02);
	vC.push_back(cell_03);
	vC.push_back(cell_04);

	Cell cellTest(111, 3, true);
	bool cellFind = false;
	UINT buf = 0;
	WCHAR dbNfo[24];
#endif

	static CensusManager cm(vC);
	static Renderer r;
	switch (message) {
	
	case WM_PAINT:

#ifdef GOL_DEBUG_MODE
		hdc = BeginPaint(hwnd, &ps);

		cm.renderState(hwnd,hdc,r);

		buf = wsprintf(dbNfo, TEXT("(%d,%d) IsFound: %d"), cellTest.getX(), cellTest.getY(), cellFind);
		TextOut(hdc, GDC.getLeft(), GDC.useLine(), dbNfo, buf);

		buf = wsprintf(dbNfo, TEXT("GDC Currentline: %d"), GDC.getCurrentLine());
		TextOut(hdc, GDC.getLeft(), GDC.useLine(), dbNfo, buf);

		EndPaint(hwnd, &ps);
#endif
		return 0;
	case WM_KEYDOWN:
		cm.stepForward();
		InvalidateRect(hwnd, NULL, true);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}