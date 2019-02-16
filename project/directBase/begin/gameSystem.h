#pragma once
#include "kGlobalDefine.h"
#include "singletonBase.h"

class player;
class mapObject;
class inGame_grape;

class gameSystem : public singletonBase<gameSystem>
{
public :
	struct set
	{
		player*			player		= nullptr;
		mapObject*		mapObject	= nullptr;
		inGame_grape*	grape		= nullptr;
	};

private :
	set _set;

public :
	set & getSet(void) { return _set; }

public:
	gameSystem() {};
	~gameSystem() {};
};

#define SGT_GAME gameSystem::getInstance()