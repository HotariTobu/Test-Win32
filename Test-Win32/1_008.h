#pragma once

//ウィンドウクラスの登録

#include <Windows.h>

int WINAPI winmain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
	HWND hwnd;
	WNDCLASS winc;

	winc.style = CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc = DefWindowProc;
	winc.cbClsExtra = winc.cbWndExtra = 0;
	winc.hInstance = hInstance;
	winc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winc.hCursor = LoadCursor(NULL, IDC_ARROW);
	winc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName = NULL;
	winc.lpszClassName = TEXT("KITTY");

	if (!RegisterClass(&winc)) {

	}

	hwnd = CreateWindow(
		TEXT("KITTY"), TEXT("Kitty on your lap"),
		WS_OVERLAPPEDWINDOW,
		100, 100, 200, 200, NULL, NULL,
		hInstance, NULL
	);

	if (hwnd == NULL) {
		return 0;
	}

	ShowWindow(hwnd, SW_SHOW);
	MessageBox(NULL, TEXT("Kitty on your lap"), TEXT("Kitty"), MB_ICONINFORMATION);

	return 0;
}