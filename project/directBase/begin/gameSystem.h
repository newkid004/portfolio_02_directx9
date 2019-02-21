#pragma once
#include "kGlobalDefine.h"
#include "singletonBase.h"

class player;
class mapObject;
class inGame_grape;
class inGame_field;

class enemyBase;

class maptool_render;

class gameSystem : public singletonBase<gameSystem>
{
public :
	struct set	// bind
	{
		player*			player		= nullptr;
		inGame_field*	field		= nullptr;

		maptool_render* map_render	= nullptr;	// delete
	};

private :
	set _set;

public :
	void update(void);
	void draw(void);

protected :
	void initField(void);

public :
	enemyBase* addEnemy(int enemyType = 1);

public :
	set & getSet(void) { return _set; }

public:
	gameSystem();
	~gameSystem();
};

#define SGT_GAME gameSystem::getInstance()