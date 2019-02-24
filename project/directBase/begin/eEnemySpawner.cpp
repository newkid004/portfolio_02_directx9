#include "eEnemySpawner.h"

#include "managerList.h"
#include "gDigit.h"

#include "inGame_field.h"

#include "enemyFactory.h"
#include "patternMeshDup.h"

eEnemySpawner::eEnemySpawner() :
	eventBase(nullptr, nullptr, 
		EVENT::TYPE::ENEMY |
		EVENT::KIND::ENEMY::BASE |
		EVENT::ACT::ENEMY::ADDED,
	SGT_GAME->getStatus().timeTotalWave)
{
	SGT_GAME->getSet().airPlane->getNextBit() =
		ATYPE_AIRPLANE |
		AIRPLANE_IDLE |
		AIRPLANE_IDLE_ON;
}

eEnemySpawner::~eEnemySpawner()
{
	gDigit::put(SGT_GAME->getStatus().digitActive, sysDigit::rideable);
	
	MN_EVENT->add(new eventBase(nullptr, nullptr,
		EVENT::TYPE::TRIGGER |
		EVENT::KIND::TRIGGER::AIR_PLANE |
		EVENT::ACT::TRIGGER::COMPLETE));
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

	if (m_stTimeAlive < 20.0f)
	{
		SGT_GAME->getSet().airPlane->getNextBit() =
			ATYPE_AIRPLANE |
			AIRPLANE_OPEN |
			AIRPLANE_OPEN_NONE;
	}
}
