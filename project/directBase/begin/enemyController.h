#pragma once
#include "kGlobalDefine.h"
#include "controllerBase.h"

#include "inGame_struct.h"
#include "AnimationDef.h"


class enemyController : public controllerBase
{
protected :
	timeEnemy_set	_infoTimeEnemy;

public :
	void update(void) override;

protected :
	void update2bit(void);
	void updateFootPrint(void) override;

	void changeBindBit(aniDefine::ANIBIT minusBit, int plusBit);

	virtual void basebit(void);
public :
	timeEnemy_set & refInfoTimeEnemy(void) { return _infoTimeEnemy; }

public:
	enemyController(characterBase* bindCharacter);
	~enemyController();
};

