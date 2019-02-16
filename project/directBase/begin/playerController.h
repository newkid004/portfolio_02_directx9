#pragma once
#include "kGlobalDefine.h"
#include "controllerBase.h"

class playerController : public controllerBase
{
public:
	playerController(characterBase* bindCharacter);
	~playerController();
};

