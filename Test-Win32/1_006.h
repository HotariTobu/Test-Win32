#pragma once

//�R�}���h���C������

#include <Windows.h>

int WINAPI winmain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
	//MessageBox(NULL, lpCmdLine, TEXT("Kitty"), MB_ICONINFORMATION);
	MessageBox(NULL, GetCommandLine(), TEXT("Kitty"), MB_ICONINFORMATION);
	return 0;
}