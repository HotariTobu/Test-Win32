#pragma once

//DCÇÃëÆê´ï€ë∂

#include <Windows.h>

#define TITLE TEXT("Kitty on your lap")

BOOL TextOutClr(HDC hdc, int x, int y, LPCTSTR str, COLORREF color) {
	if (hdc == NULL) return FALSE;

	SaveDC(hdc);
	//int hsdc = SaveDC(hdc);
	SetTextColor(hdc, color);
	TextOut(hdc, x, y, str, lstrlen(str));
	RestoreDC(hdc, -1);
	//RestoreDC(hdc, hsdc);
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	HDC hdc;
	PAINTSTRUCT ps;
	int iHdcID;
	TEXTMETRIC tm;

	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetTextMetrics(hdc, &tm);

		TextOutClr(hdc, 0, 0, TITLE, RGB(0xFF, 0, 0));
		TextOut(hdc, 0, tm.tmHeight, TITLE, lstrlen(TITLE));

		EndPaint(hwnd, &ps);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wp, lp);
}

int WINAPI winmain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
	HWND hwnd;
	MSG msg;
	WNDCLASS winc;

	winc.style = CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc = WndProc;
	winc.cbClsExtra = winc.cbWndExtra = 0;
	winc.hInstance = hInstance;
	winc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winc.hCursor = LoadCursor(NULL, IDC_ARROW);
	winc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName = NULL;
	winc.lpszClassName = TEXT("KITTY");

	if (!RegisterClass(&winc)) {
		return 0;
	}

	hwnd = CreateWindow(
		TEXT("KITTY"), TEXT("Kitty on your lap"),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL,
		hInstance, NULL
	);

	if (hwnd == NULL) {
		return 0;
	}

	while (GetMessage(&msg, NULL, 0, 0)) {
		DispatchMessage(&msg);
	}

	return msg.wParam;
}