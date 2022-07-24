#pragma once

//メッセージボックス

#include <Windows.h>

int WINAPI winmain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
	int on_button;

	on_button = MessageBox(NULL, TEXT("Do you like Nekomimi?"), TEXT("質問しています"), MB_YESNO | MB_ICONQUESTION);

	if (on_button == IDYES) {
		MessageBox(NULL, TEXT("You are nice!"), TEXT("メッセージボックス"), MB_OK);
	}
	else {
		MessageBox(NULL, TEXT("Be Killed!"), TEXT("メッセージボックス"), MB_OK);
	}

	return 0;
}