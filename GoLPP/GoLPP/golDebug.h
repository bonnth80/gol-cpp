#pragma once

#define GOL_DEBUG_MODE

#ifdef GOL_DEBUG_MODE
class GolDebugController {
private:
	int uiTop;
	int uiLeft;
	int uiCurrentLine;
	int incrementSize;
public:
	GolDebugController() {
		uiTop = 5;
		uiLeft = 5;
		uiCurrentLine = uiTop;
		incrementSize = 20;
	}

	void resetCurrentLine() { uiCurrentLine = uiTop; }
	int getCurrentLine() { return uiCurrentLine; }
	int getTop() { return uiTop; }
	int getLeft() { return uiLeft; }
	int useLine() { uiCurrentLine += incrementSize; return uiCurrentLine - incrementSize; }
};

static GolDebugController GDC;

//
//UINT buf = 0;
//WCHAR dbNfo[24];
//buf = wsprintf(dbNfo, TEXT("GDC CurrentlineX: %d"), GDC.getCurrentLine());
//TextOut(hdc, GDC.getLeft(), GDC.useLine(), dbNfo, buf);

//OutputDebugString(TEXT("Holy shit"));

#endif