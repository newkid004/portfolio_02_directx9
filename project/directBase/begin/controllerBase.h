#pragma once
#include "kGlobalDefine.h"

class characterBase;

class controllerBase
{
protected :
	characterBase* _bindCharacter = nullptr;	// delete : disable (characterManager - enemy / playerable)

public :


public :
	characterBase* & getBindCharacter(void) { return _bindCharacter; }

public:
	controllerBase(characterBase* bindCharacter);
	~controllerBase();
};

