#pragma once
#include "kGlobalDefine.h"
#include "singletonBase.h"

class player;
class mapObject;

class gameSystem : public singletonBase<gameSystem>
{
public :
	struct set
	{
		player*		player		= nullptr;
		mapObject*	mapObject	= nullptr;
	};

private :
	set _set;

public :
	set & getSet(void) { return _set; }

public:
	gameSystem() {};
	~gameSystem() {};
};

#define SN_GAME gameSystem::getInstance()