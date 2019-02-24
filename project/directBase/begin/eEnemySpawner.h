#pragma once
#include "kGlobalDefine.h"
#include "eventBase.h"

class eEnemySpawner : public eventBase
{
protected :
	float _spawnInterval = 3.0f;
	float _nextSpawn = 0.0f;


public :
	void update(void) override;

public:
	eEnemySpawner();
	~eEnemySpawner();
};

