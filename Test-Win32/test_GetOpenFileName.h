#include <windows.h>
#define TITLE TEXT("Kitty on your lap")

LRESULT CALLBACK WndProc(HWND hWnd , UINT msg , WPARAM wp , LPARAM lp) {
	static OPENFILENAME ofn = {0};
	static TCHAR strFile[MAX_PATH] , strCustom[256] = TEXT("Before files\0*.*\0\0");

	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CREATE:
		ofn.lStructSize = sizeof (OPENFILENAME);
		ofn.hwndOwner = hWnd;
		ofn.lpstrFilter = 	TEXT("Text files {*.txt}\0*.txt\0")
					TEXT("HTML files {*.htm}\0*.htm;*.html\0")
					TEXT("All files {*.*}\0*.*\0\0");
		ofn.lpstrCustomFilter = strCustom;
		ofn.nMaxCustFilter = 256;
		ofn.nFilterIndex = 0;
		ofn.lpstrFile = strFile;
		ofn.nMaxFile = MAX_PATH;
		ofn.Flags = OFN_FILEMUSTEXIST;
		return 0;
	case WM_RBUTTONUP:
		GetOpenFileName(&ofn);
		SetWindowText(hWnd , strFile);
		return 0;
	}
	return DefWindowProc(hWnd , msg , wp , lp);
}

int WINAPI winmain(HINSTANCE hInstance , HINSTANCE hPrevInstance ,
			PSTR lpCmdLine , int nCmdShow ) {
	HWND hwnd;
	MSG msg;
	WNDCLASS winc;

	winc.style		= CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc	= WndProc;
	winc.cbClsExtra	= winc.cbWndExtra	= 0;
	winc.hInstance		= hInstance;
	winc.hIcon		= LoadIcon(NULL , IDI_APPLICATION);
	winc.hCursor		= LoadCursor(NULL , IDC_ARROW);
	winc.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName	= NULL;
	winc.lpszClassName	= TEXT("KITTY");

	if (!RegisterClass(&winc)) return -1;

	hwnd = CreateWindow(
			TEXT("KITTY") , TITLE ,
			WS_OVERLAPPEDWINDOW | WS_VISIBLE ,
			CW_USEDEFAULT , CW_USEDEFAULT ,
			CW_USEDEFAULT , CW_USEDEFAULT ,
			NULL , NULL ,
			hInstance , NULL
	);

	if (hwnd == NULL) return -1;

	while(GetMessage(&msg , NULL , 0 , 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}