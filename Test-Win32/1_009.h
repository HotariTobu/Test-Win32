#pragma once

//メッセージ

#include <Windows.h>

int WINAPI winmain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
	HWND hwnd;
	MSG msg;

	hwnd = CreateWindow(
		TEXT("BUTTON"), TEXT("Kitty on your lap"),
		WS_CAPTION | WS_VISIBLE,
		100, 100, 200, 200, NULL, NULL,
		hInstance, NULL
	);

	if (hwnd == NULL) {
		return 0;
	}

	while (TRUE) {
		GetMessage(&msg, NULL, 0, 0);

		if (msg.message == WM_LBUTTONUP) {
			break;
		}

		DispatchMessage(&msg);
	}

	return 0;
}