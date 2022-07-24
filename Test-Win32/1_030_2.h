#pragma once

//キーボードイベント

#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	HDC hdc;
	static int iWidth = 10;
	int iCount;
	TCHAR tcRe[4];

	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		hdc = GetDC(hwnd);
		iWidth++;

		SelectObject(hdc, GetStockObject(WHITE_PEN));
		Rectangle(hdc, 0, 0, 400, 400);

		wsprintf(tcRe, "%d", (short)lp);
		TextOut(hdc, 10, 150, tcRe, lstrlen(tcRe));

		SelectObject(hdc, GetStockObject(BLACK_BRUSH));

		for (iCount = 0; iCount < 10000; iCount++) {
			Rectangle(hdc, 10, 10, iWidth, 100);
		}
			
		ReleaseDC(hwnd, hdc);
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