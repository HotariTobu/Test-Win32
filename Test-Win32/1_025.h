#pragma once

//ÉxÉWÉFã»ê¸

#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	HDC hdc;
	PAINTSTRUCT ps;

	static POINT pt[3];

	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CREATE:
		pt[0].x = 100;
		pt[0].y = 400;
		pt[1].x = 200;
		pt[1].y = 400;
		pt[2].x = 300;
		pt[2].y = 10;
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		MoveToEx(hdc, 0, 10, NULL);
		PolyBezierTo(hdc, pt, 3);
		MoveToEx(hdc, 0, 10, NULL);
		PolylineTo(hdc, pt, 3);
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