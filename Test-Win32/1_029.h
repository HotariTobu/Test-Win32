#pragma once

//多角形モード

#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	HDC hdc;
	PAINTSTRUCT ps;

	static POINT po[8];
	static INT imode;

	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CREATE:
		po[0].x = 10;	po[0].y = 50;
		po[1].x = 150;	po[1].y = 50;
		po[2].x = 150;	po[2].y = 150;
		po[3].x = 50;	po[3].y = 150;
		po[4].x = 50;	po[4].y = 10;
		po[5].x = 200;	po[5].y = 10;
		po[6].x = 200;	po[6].y = 125;
		po[7].x = 10;	po[7].y = 125;

		imode = MessageBox(
			NULL, TEXT("多角形モードを変更しますか?"),
			TEXT("SetPolyFillMode"), MB_YESNO
		);
		if (imode == IDYES) {
			imode = WINDING;
		}
		else {
			imode = ALTERNATE;
		}

		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		SelectObject(hdc, CreateSolidBrush(0xFF));
		SetPolyFillMode(hdc, imode);
		Polygon(hdc, po, 8);
		EndPaint(hwnd, &ps);
		DeleteObject(SelectObject(hdc, GetStockObject(WHITE_BRUSH)));
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