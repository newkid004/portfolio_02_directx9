#pragma once
#include "kGlobalDefine.h"
#include "controllerBase.h"

#include "inGame_struct.h"
#include "AnimationDef.h"


class enemyController : public controllerBase
{
private:
	bool _isFemale;

protected :
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

public :
	timeEnemy_set & refInfoTimeEnemy(void) { return _infoTimeEnemy; }

public:
	enemyController(characterBase* bindCharacter);
	~enemyController();
};

