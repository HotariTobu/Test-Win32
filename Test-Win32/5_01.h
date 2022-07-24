#pragma once

#include <Windows.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <fstream>

#include "WaveOpen.h"

void showMessage(MMRESULT mr) {
	CHAR etb[1024];
	waveOutGetErrorText(mr, etb, sizeof(WCHAR) * sizeof(etb));
	MessageBox(NULL, etb, TEXT("not work"), MB_OK);
}

int WINAPI winmain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
	int hz = 48000;//サンプリングレート
	int seconds = 5;
	int time = hz * seconds;//音の時間
	std::vector<CHAR> data;

	float frq = 1.0f / 440.0f;//平均律による基準の音の周波数

	for (int i = 0; i < time; i++) {
		data.push_back((CHAR)(CHAR_MAX * sin(M_PI * 2 * frq * i)));
	}

	for (int i = 0; i < time; i++) {
		//data.push_back((CHAR)abs(CHAR_MAX * sin(M_PI * 2 * frq * i)));
	}

	for (int i = 0; i < time; i++) {
		//data.push_back((CHAR)(127 * sin(M_PI * 2 * frq * i / hz)));
	}

	//テキストとして保存
	std::ofstream fos("wave.txt", std::ios::out);

	fos << data.size() << std::endl;
	for (auto i = data.begin(); i != data.end(); i++) {
		fos << (int)(*i) << std::endl;
	}

	fos.close();

	//waveファイルとして保存
	std::vector<double> s;
	for (auto i = data.begin(); i != data.end(); i++) {
		s.push_back(*i / (double)CHAR_MAX * DBL_MAX);
	}

	my::MONO_PCM pcm;
	pcm.bits = 16;
	pcm.fs = hz;
	pcm.length = time;
	pcm.s = &s.front();

	my::mono_wave_write(&pcm, "wave.wav");

	if (MessageBox(NULL, TEXT("再生しますか？"), TEXT("いのちだいじに"), MB_YESNO) == IDNO) {
		return 0;
	}

	LPSTR buffer = &data.front();

	WAVEFORMATEX wf;
	wf.wFormatTag = WAVE_FORMAT_PCM;//形式
	wf.nChannels = 1;//モノラルは'1' ステレオなら'2'。
	wf.nSamplesPerSec = hz;//サンプリングレート
	wf.wBitsPerSample = 16;//16ビット
	wf.nBlockAlign = wf.nChannels * wf.wBitsPerSample / 8;//計算
	wf.nAvgBytesPerSec = wf.nSamplesPerSec * wf.nBlockAlign;//計算
	wf.cbSize = 0;//拡張情報

	HWAVEOUT hWOut;//デバイス

	MMRESULT wooR = waveOutOpen(&hWOut, WAVE_MAPPER, &wf, 0, 0, CALLBACK_NULL);//デバイスを開く
	if (wooR != MMSYSERR_NOERROR) {
		showMessage(wooR);
		return -1;
	}

	WAVEHDR wh;
	wh.lpData = buffer;//  データを書き込む
	wh.dwBufferLength = time;//再生時間
	wh.dwFlags = 0;//追加のオプション
	wh.dwLoops = 1;//1回だけ再生
	wh.dwBytesRecorded = 0;//音声入力の時に使う
	wh.dwUser = 0;//オプションのユーザーデータ
	wh.lpNext = NULL;//使われない
	wh.reserved = 0;//使われない

	MMRESULT wophR = waveOutPrepareHeader(hWOut, &wh, sizeof(WAVEHDR));//バッファの準備
	if (wophR != MMSYSERR_NOERROR) {
		showMessage(wophR);
		return -2;
	}

	MMRESULT wowR = waveOutWrite(hWOut, &wh, sizeof(WAVEHDR));//再生
	if (wowR != MMSYSERR_NOERROR) {
		showMessage(wowR);
		return -3;
	}

	MessageBox(NULL, TEXT("停止しますか？"), TEXT("一時停止"), MB_OK);

	MMRESULT worR = waveOutReset(hWOut);//停止
	if (worR != MMSYSERR_NOERROR) {
		showMessage(worR);
		return -4;
	}

	MMRESULT wouhR = waveOutUnprepareHeader(hWOut, &wh, sizeof(WAVEHDR));//バッファの解放
	if (wouhR != MMSYSERR_NOERROR) {
		showMessage(wouhR);
		return -5;
	}

	MMRESULT wocR = waveOutClose(hWOut);//デバイスの解放
	if (wocR != MMSYSERR_NOERROR) {
		showMessage(wocR);
		return -6;
	}

	return 0;
}