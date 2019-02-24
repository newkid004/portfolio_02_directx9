#include "eEnemySpawner.h"

#include "managerList.h"
#include "gDigit.h"

#include "inGame_field.h"

#include "enemyFactory.h"

eEnemySpawner::eEnemySpawner() :
	eventBase(nullptr, nullptr, 
		EVENT::TYPE::ENEMY |
		EVENT::KIND::ENEMY::BASE |
		EVENT::ACT::ENEMY::ADDED,
	SGT_GAME->getStatus().timeTotalWave)
{
}

eEnemySpawner::~eEnemySpawner()
{
	gDigit::put(SGT_GAME->getStatus().digitActive, sysDigit::rideable);
}

void eEnemySpawner::update(void)
{
	eventBase::update();

	static int & digitActive = SGT_GAME->getStatus().digitActive;
	SGT_GAME->getStatus().timeLeftWave = m_stTimeAlive;

	if (gDigit::chk(digitActive, sysDigit::enemySpawn))
	{
		float runningTime = MN_TIME->getRunningTime();

		if (_nextSpawn < runningTime)
		{
			_nextSpawn = runningTime + _spawnInterval;
			enemyFactory::recycleEnemy(1);
		}
	}
}
