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
	int hz = 48000;//�T���v�����O���[�g
	int seconds = 5;
	int time = hz * seconds;//���̎���
	std::vector<CHAR> data;

	float frq = 1.0f / 440.0f;//���ϗ��ɂ���̉��̎��g��

	for (int i = 0; i < time; i++) {
		data.push_back((CHAR)(CHAR_MAX * sin(M_PI * 2 * frq * i)));
	}

	for (int i = 0; i < time; i++) {
		//data.push_back((CHAR)abs(CHAR_MAX * sin(M_PI * 2 * frq * i)));
	}

	for (int i = 0; i < time; i++) {
		//data.push_back((CHAR)(127 * sin(M_PI * 2 * frq * i / hz)));
	}

	//�e�L�X�g�Ƃ��ĕۑ�
	std::ofstream fos("wave.txt", std::ios::out);

	fos << data.size() << std::endl;
	for (auto i = data.begin(); i != data.end(); i++) {
		fos << (int)(*i) << std::endl;
	}

	fos.close();

	//wave�t�@�C���Ƃ��ĕۑ�
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

	if (MessageBox(NULL, TEXT("�Đ����܂����H"), TEXT("���̂���������"), MB_YESNO) == IDNO) {
		return 0;
	}

	LPSTR buffer = &data.front();

	WAVEFORMATEX wf;
	wf.wFormatTag = WAVE_FORMAT_PCM;//�`��
	wf.nChannels = 1;//���m������'1' �X�e���I�Ȃ�'2'�B
	wf.nSamplesPerSec = hz;//�T���v�����O���[�g
	wf.wBitsPerSample = 16;//16�r�b�g
	wf.nBlockAlign = wf.nChannels * wf.wBitsPerSample / 8;//�v�Z
	wf.nAvgBytesPerSec = wf.nSamplesPerSec * wf.nBlockAlign;//�v�Z
	wf.cbSize = 0;//�g�����

	HWAVEOUT hWOut;//�f�o�C�X

	MMRESULT wooR = waveOutOpen(&hWOut, WAVE_MAPPER, &wf, 0, 0, CALLBACK_NULL);//�f�o�C�X���J��
	if (wooR != MMSYSERR_NOERROR) {
		showMessage(wooR);
		return -1;
	}

	WAVEHDR wh;
	wh.lpData = buffer;//  �f�[�^����������
	wh.dwBufferLength = time;//�Đ�����
	wh.dwFlags = 0;//�ǉ��̃I�v�V����
	wh.dwLoops = 1;//1�񂾂��Đ�
	wh.dwBytesRecorded = 0;//�������͂̎��Ɏg��
	wh.dwUser = 0;//�I�v�V�����̃��[�U�[�f�[�^
	wh.lpNext = NULL;//�g���Ȃ�
	wh.reserved = 0;//�g���Ȃ�

	MMRESULT wophR = waveOutPrepareHeader(hWOut, &wh, sizeof(WAVEHDR));//�o�b�t�@�̏���
	if (wophR != MMSYSERR_NOERROR) {
		showMessage(wophR);
		return -2;
	}

	MMRESULT wowR = waveOutWrite(hWOut, &wh, sizeof(WAVEHDR));//�Đ�
	if (wowR != MMSYSERR_NOERROR) {
		showMessage(wowR);
		return -3;
	}

	MessageBox(NULL, TEXT("��~���܂����H"), TEXT("�ꎞ��~"), MB_OK);

	MMRESULT worR = waveOutReset(hWOut);//��~
	if (worR != MMSYSERR_NOERROR) {
		showMessage(worR);
		return -4;
	}

	MMRESULT wouhR = waveOutUnprepareHeader(hWOut, &wh, sizeof(WAVEHDR));//�o�b�t�@�̉��
	if (wouhR != MMSYSERR_NOERROR) {
		showMessage(wouhR);
		return -5;
	}

	MMRESULT wocR = waveOutClose(hWOut);//�f�o�C�X�̉��
	if (wocR != MMSYSERR_NOERROR) {
		showMessage(wocR);
		return -6;
	}

	return 0;
}