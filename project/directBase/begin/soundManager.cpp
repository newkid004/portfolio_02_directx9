#include "soundManager.h"

using namespace FMOD;
using namespace std;

HRESULT cSound::init(System* system)
{
	_system = system;
	_sound = NULL;
	_channel = NULL;

	return S_OK;
}

void cSound::release(void)
{
	if (_channel != NULL)	_channel->stop();
	if (_sound != NULL)		_sound->release();
}

void cSound::update(void)
{
	_system->update();
}

void cSound::play(float volume, float pitch)
{
	FMOD_RESULT r;
	r = _system->playSound(FMOD_CHANNEL_FREE, _sound, false, &_channel);
	if (0 <= volume)
	{
		_channel->setVolume(volume);
	}
	if (pitch != 0.0f)
		_channel->setFrequency(44100 * pitch);

	if (_cGroup != NULL)
		_channel->setChannelGroup(_cGroup);
}

void cSound::stop(void)
{
	if (isPlaySound())
	{
		_channel->stop();

		if (_cGroup != NULL)
			_channel->setChannelGroup(_cGroup);
	}
}

void cSound::pause(void)
{
	_channel->setPaused(true);

	if (_cGroup != NULL)
		_channel->setChannelGroup(_cGroup);
}

void cSound::resum(void)
{
	_channel->setPaused(false);

	if (_cGroup != NULL)
		_channel->setChannelGroup(_cGroup);
}

bool cSound::isPlaySound()
{
	bool bGetter;
	_channel->isPlaying(&bGetter);
	return bGetter;
}

bool cSound::isPauseSound()
{
	bool bGetter;
	_channel->getPaused(&bGetter);
	return bGetter;
}

void cSound::setVolume(float volume)
{
	volume = volume < 0 ? 0 : volume;
	volume = 1.0f < volume ? 1.0f : volume;

	_channel->setVolume(volume);
}

float cSound::getVolume(void)
{
	float fGetter;
	_channel->getVolume(&fGetter);
	return fGetter;
}

bool cSound::getMute(void)
{
	bool isMute;
	_channel->getMute(&isMute);
	return isMute;
}

unsigned int cSound::getPlayPos()
{
	unsigned int iGetter;
	_channel->getPosition(&iGetter, FMOD_TIMEUNIT_MS);
	return iGetter;
}

unsigned int cSound::getSoundLength()
{
	unsigned int iGetter;
	_sound->getLength(&iGetter, FMOD_TIMEUNIT_MS);
	return iGetter;
}


HRESULT soundManager::init(void)
{
	System_Create(&_system);
	if (_maxSoundCustom != -1)
		_system->init(_maxSoundCustom + TEMP_SOUND, FMOD_INIT_NORMAL, 0);
	else
		_system->init(TOTAL_SOUND_COUNT, FMOD_INIT_NORMAL, 0);

	_system->getMasterChannelGroup(&_cgMaster);

	_system->createChannelGroup("BGM", &_cgBGM);
	_system->createChannelGroup("SE", &_cgSE);
	_cgMaster->addGroup(_cgBGM);
	_cgMaster->addGroup(_cgSE);

	return S_OK;
}

void soundManager::release(void)
{
	// 사운드 삭제
	if (_mSound.size() != 0)
	{
		unordered_map<string, cSound*>::iterator iter = _mSound.begin();
		for (; iter != _mSound.end();)
		{
			iter->second->release();
			SAFE_DELETE(iter->second);

			iter = _mSound.erase(iter);
		}
	}
	if (_system != NULL)
	{
		_cgBGM->release();
		_cgSE->release();

		_system->release();
		_system->close();
	}
}

void soundManager::update(void)
{
	unordered_map<string, cSound*>::iterator iter = _mSound.begin();
	for (; iter != _mSound.end(); ++iter) iter->second->update();
}

cSound* soundManager::addSound(const char* soundName, const char * fileName, bool background, bool loop)
{
	// 이미 있으면 리턴
	cSound* snd = find(soundName);
	if (snd != NULL) return snd;

	snd = new cSound;
	snd->init(_system);

	if (loop)
	{
		if (background)
		{
			// CreateStream(파일 이름, 사운드를 열기 위한 옵션, 재생 시 개발자에게 정보전달 포인터 사용유무 결정, 사운드 오브젝트)

			// FMOD_LOOP_NORMAL : 루프 ON
			snd->_system->createStream(fileName, FMOD_LOOP_NORMAL, 0, &snd->_sound);
			snd->_cGroup = _cgBGM;
		}
		else
		{
			// 여러 음원 동시사용 가능(효과음)
			snd->_system->createSound(fileName, FMOD_LOOP_NORMAL, 0, &snd->_sound);
			snd->_cGroup = _cgSE;
		}
	}
	else
	{
		// 한 번 플레이
		snd->_system->createSound(fileName, FMOD_DEFAULT, 0, &snd->_sound);
	}
	snd->_channel->setVolume(1.0f);

	// 맵에 저장
	_mSound.insert(make_pair(soundName, snd));

	return snd;
}

cSound * soundManager::find(string soundName)
{
	unordered_map<string, cSound*>::iterator snd = _mSound.find(soundName);

	if (snd != _mSound.end()) return snd->second;

	return NULL;
}

void soundManager::stopAll(void)
{
	unordered_map<string, cSound*>::iterator iter = _mSound.begin();
	for (; iter != _mSound.end(); ++iter) iter->second->stop();
}
