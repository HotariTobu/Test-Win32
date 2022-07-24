#pragma once

//ÉäÅ[ÉWÉáÉìÇÃê∂ê¨

#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	HDC hdc;
	PAINTSTRUCT ps;
	HRGN hrgn;
	static POINT pt[3];

	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CREATE:
		pt[0].x = 10; pt[0].y = 10;
		pt[1].x = 100; pt[1].y = 10;
		pt[2].x = 30; pt[2].y = 100;
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		SelectObject(hdc, GetStockObject(GRAY_BRUSH));

		hrgn = CreatePolygonRgn(pt, 3, ALTERNATE);
		PaintRgn(hdc, hrgn);

		DeleteObject(hrgn);
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
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}