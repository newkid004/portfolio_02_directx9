#include "soundManager.h"
#include "windowManager.h"
#include "timeManager.h"

#include "sound.h"

#define MN_TIME GET_TIME_MANAGER()

soundManager::soundManager() :
	_volumeSE(1.0f),
	_volumeBGM(1.0f)
{
}

soundManager::~soundManager()
{
	SAFE_RELEASE(_primaryBuffer);
	SAFE_RELEASE(_directSound);
}

void soundManager::init(void)
{
	_directSound = createDirectSound();
	_primaryBuffer = createPrimaryBuffer();
}

void soundManager::addSound(sound * input)
{
	auto & viewContainer = input->getPlayInfo()->isBGM ? _vSoundBGM : _vSoundSE;

	viewContainer.push_back(input);
}

void soundManager::delSound(sound * input)
{
	auto & viewContainer = input->getPlayInfo()->isBGM ? _vSoundBGM : _vSoundSE;

	for (int i = 0; i < viewContainer.size(); ++i)
	{
		if (viewContainer[i] == input)
		{
			viewContainer.erase(viewContainer.begin() + i);
			break;
		}
	}
}

void soundManager::setVolumeSE(float input)
{
	_volumeSE = input;

	for (auto snd : _vSoundSE)
		snd->setVolue(input);
}

void soundManager::setVolumeBGM(float input)
{
	_volumeBGM = input;

	for (auto snd : _vSoundBGM)
		snd->setVolue(input);
}

LPDIRECTSOUND soundManager::createDirectSound(void)
{
	LPDIRECTSOUND result = nullptr;

	DirectSoundCreate(NULL, &result, NULL);
	result->SetCooperativeLevel(GET_WINDOW_MANAGER()->getHWnd(), DSSCL_PRIORITY);	// 주 버퍼 제어 가능

	return result;
}

LPDIRECTSOUNDBUFFER soundManager::createPrimaryBuffer(void)
{
	LPDIRECTSOUNDBUFFER result = nullptr;

	DSBUFFERDESC bufDesc;
	ZeroMemory(&bufDesc, sizeof(bufDesc));

	/*
		주 버퍼는 직접적으로 생성 불가
		DSBUFFERDESC.dwFlags에 DSCAPS_PRIMARYBUFFER 옵션을 설정하는 것은
		주 버퍼의 포인터를 얻어오는 것을 의미
	*/
	bufDesc.dwSize = sizeof(bufDesc);
	bufDesc.dwFlags = DSBCAPS_PRIMARYBUFFER;

	_directSound->CreateSoundBuffer(&bufDesc, &result, NULL);

	// 버퍼 포맷 설정
	WAVEFORMATEX wavFormat;
	ZeroMemory(&wavFormat, sizeof(wavFormat));

	wavFormat.cbSize = sizeof(wavFormat);											
	wavFormat.wFormatTag = WAVE_FORMAT_PCM;											
	wavFormat.nChannels = 2;														// 채널 개수
	wavFormat.nSamplesPerSec = 22050;												// 초당 샘플링 횟수
	wavFormat.wBitsPerSample = 16;													// 한 샘플의 비트 수
	wavFormat.nBlockAlign = (wavFormat.wBitsPerSample / 8) * wavFormat.nChannels;	// 한 블럭에 대한 Byte 크기
	wavFormat.nAvgBytesPerSec = wavFormat.nBlockAlign * wavFormat.nSamplesPerSec;	// 초당 샘플링 Byte

	result->SetFormat(&wavFormat);

	return result;
}
