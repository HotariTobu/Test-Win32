#pragma once

#include <windows.h>
#define TITLE 	TEXT("Kitty on your lap")
#define SRATE 	11025

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	static HWAVEOUT hWave;
	static BYTE *bWave;
	DWORD dwCount, dwWaveL = 0, dwWaveR = 0;
	WAVEFORMATEX wfe;
	WAVEHDR whdr;

	switch (msg) {
	case WM_DESTROY:
		waveOutReset(hWave);
		waveOutUnprepareHeader(hWave, &whdr, sizeof(WAVEHDR));
		free(bWave);
		waveOutClose(hWave);
		PostQuitMessage(0);
		return 0;
	case WM_CREATE:
		bWave = (BYTE*)malloc(SRATE * 2);

		for (dwCount = 0; dwCount < SRATE * 2; dwCount++) {
			if (dwWaveL > 256) dwWaveL = 0;
			*(bWave + dwCount++) = dwWaveL;
			dwWaveL += 10;

			if (dwWaveR > 256) dwWaveR = 0;
			*(bWave + dwCount) = dwWaveR;
			dwWaveR += 20;
		}
		wfe.wFormatTag = WAVE_FORMAT_PCM;
		wfe.nChannels = 2;
		wfe.nSamplesPerSec = SRATE;
		wfe.nAvgBytesPerSec = SRATE;
		wfe.wBitsPerSample = 8;
		wfe.nBlockAlign = wfe.nChannels * wfe.wBitsPerSample / 8;

		waveOutOpen(&hWave,
			WAVE_MAPPER, &wfe, 0, 0, CALLBACK_NULL);

		whdr.lpData = (LPSTR)bWave;
		whdr.dwBufferLength = SRATE * 2;
		whdr.dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
		whdr.dwLoops = 5;
		waveOutPrepareHeader(hWave, &whdr, sizeof(WAVEHDR));
		waveOutWrite(hWave, &whdr, sizeof(WAVEHDR));
		return 0;
	}
	return DefWindowProc(hWnd, msg, wp, lp);
}

int WINAPI winmain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, int nCmdShow) {
	HWND hWnd;
	MSG msg;
	WNDCLASS winc;

	winc.style = CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc = WndProc;
	winc.cbClsExtra = winc.cbWndExtra = 0;
	winc.hInstance = hInstance;
	winc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winc.hCursor = LoadCursor(NULL, IDC_ARROW);
	winc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName = TEXT("KITTY");
	winc.lpszClassName = TEXT("KITTY");

	if (!RegisterClass(&winc)) return 1;

	hWnd = CreateWindow(
		TEXT("KITTY"), TITLE,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL
	);

	if (hWnd == NULL) return 1;

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}