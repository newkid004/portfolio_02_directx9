#pragma once
#include "kGlobalDefine.h"
#include "controllerBase.h"

#include "inGame_struct.h"

class enemyController : public controllerBase
{
protected :
	timeEnemy_set	_infoTimeEnemy;

public :
	void update(void) override;

protected :
	void update2bit(void);

public :
	timeEnemy_set & refInfoTimeEnemy(void) { return _infoTimeEnemy; }

public:
	enemyController(characterBase* bindCharacter);
	~enemyController();
};

