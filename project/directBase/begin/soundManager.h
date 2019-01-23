#pragma once
#include "kGlobalDefine.h"

class sound;

using namespace std;

class soundManager
{
public :
	enum 
	{
		MAX_NUM_DUPLICATE_EFFECT_SOUND = 5
	};

private :
	vector<sound*> _vSoundSE;
	vector<sound*> _vSoundBGM;

	LPDIRECTSOUND		_directSound = nullptr;
	LPDIRECTSOUNDBUFFER	_primaryBuffer = nullptr;

	float _volumeSE = 1.0f;
	float _volumeBGM = 1.0f;

public :
	void init(void);

public :
	void addSound(sound* input);
	void delSound(sound* input);

public:
	LPDIRECTSOUND getDirectSound(void) const { return _directSound; };
	LPDIRECTSOUNDBUFFER getPrimaryBuffer(void) const { return _primaryBuffer; };

	float getVolumeSE(void) { return _volumeSE; }
	float getVolumeBGM(void) { return _volumeBGM; }

	void setVolumeSE(float input);
	void setVolumeBGM(float input);

private :
	LPDIRECTSOUND createDirectSound(void);
	LPDIRECTSOUNDBUFFER createPrimaryBuffer(void);

public :
	DECLARE_SINGLETON(soundManager);

private :
	soundManager();
	virtual ~soundManager();
};

