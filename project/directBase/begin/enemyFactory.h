#pragma once
#include "kGlobalDefine.h"

class enemyBase;

class enemyFactory
{
public :
	static enemyBase* createEnemy(int type);
	static enemyBase* recycleEnemy(int type);

private :
	enemyFactory() {};
	~enemyFactory() {};
};

