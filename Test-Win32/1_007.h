#pragma once

//�E�B���h�E�����

#include <Windows.h>

int WINAPI winmain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
	HWND hwnd = CreateWindow(
		TEXT("STATIC"), TEXT("Kitty on your lap"),
		WS_CAPTION,
		100, 100, 200, 200, NULL, NULL,
		hInstance, NULL
	);

	hwnd = CreateWindowEx(WS_EX_TOOLWINDOW,
		TEXT("STATIC"), TEXT("Kitty on your lap"),
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