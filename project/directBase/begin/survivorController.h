#pragma once
#include "kGlobalDefine.h"
#include "controllerBase.h"

class survivorController : public controllerBase
{
public:
	survivorController(characterBase* bindCharacter);
	~survivorController();
};

