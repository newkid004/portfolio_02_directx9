#pragma once
#include "kGlobalDefine.h"
#include "singletonBase.h"
// fmod �߰�
#include "inc/fmod.hpp"

#pragma comment (lib, "lib/fmodex_vc.lib")
/*
FMOD
- ���忣�� ���̺귯��
- �𸮾�, ����Ƽ���� ���̼��� ������� ���� �⺻ ����Ǿ� ����
*/

#define MAX_SOUND 64
#define TEMP_SOUND 5
#define TOTAL_SOUND_COUNT (MAX_SOUND + TEMP_SOUND)

class cSound
{
public:
	FMOD::System* _system;
	FMOD::Sound* _sound;
	FMOD::Channel* _channel;

	FMOD::ChannelGroup* _cGroup = NULL;

public:
	HRESULT init(FMOD::System* system);
	void release(void);
	void update(void);

public:
	// ���� ����
	void play(float volume = -1.0f, float pitch = 0.0f);
	void stop(void);
	void pause(void);
	void resum(void);

	bool isPlaySound(void);
	bool isPauseSound(void);

	void setVolume(float volume);
	float getVolume(void);

	void setMute(bool isMute) { _channel->setMute(isMute); };
	bool getMute(void);

	unsigned int getPlayPos(void);
	void setPlayPos(unsigned int posMs) { _channel->setPosition(posMs, FMOD_TIMEUNIT_MS); };

	unsigned int getSoundLength();

public:
	cSound() {};
	~cSound() {};
};

class soundManager : public singletonBase<soundManager>
{
private:
	int _maxSoundCustom;

	FMOD::System* _system;
	std::unordered_map<std::string, cSound*> _mSound;

	FMOD::ChannelGroup* _cgMaster;

	FMOD::ChannelGroup* _cgBGM;
	FMOD::ChannelGroup* _cgSE;

public:
	HRESULT init(void);
	void release(void);
	void update(void);

	// ���� ����
	cSound* addSound(const char* soundName, const char * fileName, bool background, bool loop);
	cSound* find(std::string soundName);

	// ���� ����
	void stopAll(void);

	int& getMaxSoundCustom(void) { return _maxSoundCustom; }

	FMOD::ChannelGroup* getBGM(void) { return _cgBGM; };
	FMOD::ChannelGroup* getSE(void) { return _cgSE; };

public:
	soundManager() { _maxSoundCustom = -1; };
	~soundManager() {};
};

#define MN_SND soundManager::getInstance()