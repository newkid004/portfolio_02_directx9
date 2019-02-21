#include "enemyFactory.h"

#include "managerList.h"
#include "gFunc.h"

#include "inGame_digit.h"
#include "inGame_field.h"

#include "enemyBase.h"

using DIGIT = inGame_digit::ENEMY;
#define DIGIT_CHK(d) (type & d)

enemyBase * enemyFactory::createEnemy(int type)
{
	enemyBase* result = nullptr;

	if (DIGIT_CHK(DIGIT::TANK))
	{

	}
	else if (DIGIT_CHK(DIGIT::COMMON))
	{
		int look = gFunc::rndInt(0, 2);

		switch (look)
		{
		case 0: result = new enemyBase(MN_SRC->getPatternMesh("enemy_male_0"));		break;
		case 1: result = new enemyBase(MN_SRC->getPatternMesh("enemy_male_1"));		break;
		case 2: result = new enemyBase(MN_SRC->getPatternMesh("enemy_female_0"));	break;
		}
	}

	return result;
}

enemyBase * enemyFactory::recycleEnemy(int type)
{
	enemyBase* result = nullptr;

	auto & vEnemyList = SGT_GAME->getSet().field->getList().vEnemy;

	for (auto i : vEnemyList)
	{
		if (i->refEnemyType() == type)
		{
			result = i;
			break;
		}
	}

	if (DIGIT_CHK(DIGIT::TANK))
	{

	}
	else if (DIGIT_CHK(DIGIT::COMMON))
	{
		int look = gFunc::rndInt(0, 2);

		switch (look)
		{
		case 0: result = new enemyBase(MN_SRC->getPatternMesh("enemy_male_0"));		break;
		case 1: result = new enemyBase(MN_SRC->getPatternMesh("enemy_male_1"));		break;
		case 2: result = new enemyBase(MN_SRC->getPatternMesh("enemy_female_0"));	break;
		}
	}

	return result;
}
