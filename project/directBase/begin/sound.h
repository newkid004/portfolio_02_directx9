#pragma once
#include "kGlobalDefine.h"

class sound
{
public :
	struct wavInfo
	{
		BYTE* nBytes = nullptr;
		DWORD numByte = 0;
		WAVEFORMATEX format = { 0 };
	};
	struct playInfo
	{
		BOOL isBGM = FALSE;
		float length = 0;
		float* lastRunTime = nullptr;
		int currentRunIndex = 0;
		int maxRunIndex = 0;
		float volume = 1.0f;
	};

protected :
#define run_callback(excute) runBuffer([&](LPDIRECTSOUNDBUFFER buffer)->void { excute; })

protected :
	wavInfo* _wavInfo = nullptr;
	playInfo _playInfo;
	LPDIRECTSOUNDBUFFER* _secondBuffer = nullptr;
	DWORD _flag = 0;

public :
	virtual void play(void);
	virtual void stop(void);

	void setVolue(float volume);

public :
	bool isLoop(void) { return _flag & DSBPLAY_LOOPING; }

public :
	wavInfo const* getWavInfo(void) { return _wavInfo; }
	playInfo const* getPlayInfo(void) { return &_playInfo; }
	LPDIRECTSOUNDBUFFER getBuffer(void) { return _secondBuffer[_playInfo.currentRunIndex]; }
	LPDIRECTSOUNDBUFFER const* getBufferTotal(void) { return _secondBuffer; }

	void setFlag(DWORD flag) { _flag = flag; }

private :
	static LPDIRECTSOUNDBUFFER createSecondBuffer(sound* s);
	void runBuffer(const std::function<void(LPDIRECTSOUNDBUFFER)> & callback);

public:
	sound(wavInfo* info, bool isBGM);
	virtual ~sound();
};