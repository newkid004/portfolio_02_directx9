#pragma once
#include "kGlobalDefine.h"

#include "controllerBase.h"

class enemyController : public controllerBase
{
public:
	enemyController(characterBase* bindCharacter);
	~enemyController();
};

