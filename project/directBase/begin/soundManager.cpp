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
	result->SetCooperativeLevel(GET_WINDOW_MANAGER()->getHWnd(), DSSCL_PRIORITY);	// �� ���� ���� ����

	return result;
}

LPDIRECTSOUNDBUFFER soundManager::createPrimaryBuffer(void)
{
	LPDIRECTSOUNDBUFFER result = nullptr;

	DSBUFFERDESC bufDesc;
	ZeroMemory(&bufDesc, sizeof(bufDesc));

	/*
		�� ���۴� ���������� ���� �Ұ�
		DSBUFFERDESC.dwFlags�� DSCAPS_PRIMARYBUFFER �ɼ��� �����ϴ� ����
		�� ������ �����͸� ������ ���� �ǹ�
	*/
	bufDesc.dwSize = sizeof(bufDesc);
	bufDesc.dwFlags = DSBCAPS_PRIMARYBUFFER;

	_directSound->CreateSoundBuffer(&bufDesc, &result, NULL);

	// ���� ���� ����
	WAVEFORMATEX wavFormat;
	ZeroMemory(&wavFormat, sizeof(wavFormat));

	wavFormat.cbSize = sizeof(wavFormat);											
	wavFormat.wFormatTag = WAVE_FORMAT_PCM;											
	wavFormat.nChannels = 2;														// ä�� ����
	wavFormat.nSamplesPerSec = 22050;												// �ʴ� ���ø� Ƚ��
	wavFormat.wBitsPerSample = 16;													// �� ������ ��Ʈ ��
	wavFormat.nBlockAlign = (wavFormat.wBitsPerSample / 8) * wavFormat.nChannels;	// �� ���� ���� Byte ũ��
	wavFormat.nAvgBytesPerSec = wavFormat.nBlockAlign * wavFormat.nSamplesPerSec;	// �ʴ� ���ø� Byte

	result->SetFormat(&wavFormat);

	return result;
}
