#include "sound.h"

#include "soundManager.h"
#include "resourceManager.h"
#include "timeManager.h"

#define MN_SND GET_SOUND_MANAGER()
#define MN_SRC GET_RESOURCE_MANAGER()
#define MN_TIME GET_TIME_MANAGER()

using namespace std;

sound::sound(wavInfo* info, bool isBGM)
{
	_wavInfo = info;

	// 플레이 정보 설정
	int bufCount = (soundManager::MAX_NUM_DUPLICATE_EFFECT_SOUND - 1) * (!isBGM) + 1;

	_playInfo.isBGM = isBGM;
	_playInfo.length = ((float)_wavInfo->numByte) / ((float)_wavInfo->format.nAvgBytesPerSec);

	_playInfo.maxRunIndex = bufCount;
	_playInfo.lastRunTime = new float[bufCount];
	for (int i = 0; i < bufCount; ++i)
		_playInfo.lastRunTime[i] = (float)-INT_MAX;

	// 버퍼 설정
	_secondBuffer = new LPDIRECTSOUNDBUFFER[bufCount];
	for (int i = 0; i < bufCount; ++i)
		_secondBuffer[i] = createSecondBuffer(this);

	// 사운드 매니저에 추가
	MN_SND->addSound(this);
}

sound::~sound()
{
	// 사운드 매니저에 제거
	MN_SND->delSound(this);

	// 해제
	SAFE_FREE(_wavInfo->nBytes);
	SAFE_DELETE(_wavInfo);

	SAFE_DELETE_ARRAY(_playInfo.lastRunTime);

	for (int i = 0; i < _playInfo.maxRunIndex; ++i)
		SAFE_RELEASE(_secondBuffer[i]);
	SAFE_DELETE_ARRAY(_secondBuffer);
}

void sound::play(void)
{
	if (_playInfo.lastRunTime[_playInfo.currentRunIndex] + _playInfo.length < MN_TIME->getRunningTime())
	{
		getBuffer()->Play(0, 0, _flag);
		_playInfo.lastRunTime[_playInfo.currentRunIndex] = MN_TIME->getRunningTime();
		_playInfo.currentRunIndex = (_playInfo.currentRunIndex + 1) % _playInfo.maxRunIndex;
	}
}

void sound::stop(void)
{
	_playInfo.currentRunIndex = 0;
	ZeroMemory(_playInfo.lastRunTime, sizeof(float) * _playInfo.maxRunIndex);

	runBuffer([](LPDIRECTSOUNDBUFFER buf)->void { buf->Stop(); });
}

void sound::setVolue(float volume)
{
	float fVolume = min(1.0f, _playInfo.volume);
	fVolume = max(0.0f, fVolume);

	runBuffer([&](LPDIRECTSOUNDBUFFER buf)->void { buf->SetVolume((1.0f - fVolume) * DSBVOLUME_MIN); });
}

LPDIRECTSOUNDBUFFER sound::createSecondBuffer(sound* s)
{
	DSBUFFERDESC bufDesc;
	ZeroMemory(&bufDesc, sizeof(bufDesc));

	bufDesc.dwSize = sizeof(bufDesc);
	bufDesc.dwBufferBytes = s->_wavInfo->numByte;
	bufDesc.guid3DAlgorithm = GUID_NULL;
	bufDesc.lpwfxFormat = &s->_wavInfo->format;
	bufDesc.dwFlags = DSBCAPS_STATIC | DSBCAPS_CTRLVOLUME; // | DSBCAPS_GLOBALFOCUS;

	// 사운드 정보 설정
	LPDIRECTSOUNDBUFFER result = nullptr;
	MN_SND->getDirectSound()->CreateSoundBuffer(&bufDesc, &result, NULL);

	BYTE* byteA = nullptr;
	BYTE* byteB = nullptr;
	DWORD numBytesA = 0;
	DWORD numBytesB = 0;

	if (SUCCEEDED(result->Lock(
		0,
		s->_wavInfo->numByte,
		(void**)&byteA, &numBytesA,
		(void**)&byteB, &numBytesB,
		0)))
	{
		CopyMemory(byteA, s->_wavInfo->nBytes, s->_wavInfo->numByte);
		result->Unlock(NULL, 0, NULL, 0);
	}

	return result;
}

void sound::runBuffer(const function<void(LPDIRECTSOUNDBUFFER)>& callback)
{
	for (int i = 0; i < _playInfo.maxRunIndex; ++i)
		callback(_secondBuffer[i]);
}
