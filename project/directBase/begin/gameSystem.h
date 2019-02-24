#pragma once
#include "kGlobalDefine.h"
#include "singletonBase.h"

class player;
class mapObject;
class inGame_grape;
class inGame_field;
class patternMeshDup;

class enemyBase;

class maptool_render;
class skyBox;

class gameSystem : public singletonBase<gameSystem>
{
public :
	struct set	// bind
	{
		player*			player		= nullptr;
		inGame_field*	field		= nullptr;
		mapObject*		map			= nullptr;
		maptool_render* map_render	= nullptr;	// delete
		patternMeshDup*	airPlane	= nullptr;
	};

	struct status
	{
		struct digit
		{
			globalDigit wave		= 1 << 0;
			globalDigit enemySpawn	= 1 << 1;
			globalDigit rideable	= 1 << 2;
		};
		int digitActive = 0.0f;

		float timeTotalWave = 180.0f;
		float timeLeftWave = 0.0f;		// ref

		int numMaximumEnemy = 10;
	};

private :
	set _set;
	status _status;
	skyBox* _skyBox;
public :
	void update(void);
	void draw(void);

protected :
	void initField(void);
	void initAirPlane(void);
	skyBox* createSkyBox(void);

public :
	enemyBase* addEnemy(int enemyType = 1);
	void setDebugEnable(bool value);

public :
	set & getSet(void) { return _set; }
	status & getStatus(void) { return _status; }

public:
	gameSystem();
	~gameSystem();
};

#define SGT_GAME gameSystem::getInstance()
using sysDigit = gameSystem::status::digit;