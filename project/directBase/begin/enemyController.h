#pragma once
#include "kGlobalDefine.h"
#include "controllerBase.h"

#include "inGame_struct.h"
#include "AnimationDef.h"


class enemyController : public controllerBase
{
private:
	struct soundTime
	{
		std::string mouse = "breathing";
		float footSoundDelay = 0.3f;
		float footSoundStart = 0.0f;
		float mouseSoundDelay = 2.5f;
		float mouseSoundStart = 0.0f;
		float effectSoundDelay = 1.5f;
		float effectSoundStart = 0.0f;
	};

	bool _isFemale;

protected :
	
	soundTime _soundT;
	timeEnemy_set	_infoTimeEnemy;
	float _delay;

public :
	void update(void) override;

protected :
	void updateFootPrint(void) override;
	virtual void update2bit(void);

	virtual void baseBit(void);


	void changeBindBit(aniDefine::ANIBIT minusBit, int plusBit);

	float getDistance2player(void);

	virtual void updateBeShot(void);
public :
	timeEnemy_set & refInfoTimeEnemy(void) { return _infoTimeEnemy; }

public:
	enemyController(characterBase* bindCharacter);
	~enemyController();
};

