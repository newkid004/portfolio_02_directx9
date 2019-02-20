#pragma once
#include "kGlobalDefine.h"
#include "enemyController.h"

#include "inGame_struct.h"
#include "AnimationDef.h"


class tankController : public enemyController
{
protected:
	virtual void update2bit(void);

	virtual void baseBit(void);

public:
	tankController(characterBase* bindCharacter);
	~tankController();
};

