#include "enemyFactory.h"

#include "managerList.h"
#include "gFunc.h"
#include "gDigit.h"

#include "eventBase.h"
#include "eventDef.h"

#include "inGame_digit.h"
#include "inGame_field.h"
#include "inGame_grape.h"

#include "enemyBase.h"

using DIGIT = inGame_digit;
#define DIGIT_CHK(d) (type & d)

enemyBase * enemyFactory::createEnemy(int type)
{
	enemyBase* result = nullptr;

	if (DIGIT_CHK(DIGIT::ENEMY::TANK))
	{

	}
	else if (DIGIT_CHK(DIGIT::ENEMY::COMMON))
	{
		int look = gFunc::rndInt(0, 2);

		switch (look)
		{
		case 0: result = new enemyBase(MN_SRC->getPatternMesh("enemy_male_0"));		break;
		case 1: result = new enemyBase(MN_SRC->getPatternMesh("enemy_male_1"));		break;
		case 2: result = new enemyBase(MN_SRC->getPatternMesh("enemy_female_0"));	break;
		}
	}

	auto & vSpawnPos = SGT_GAME->getSet().field->getList().vSpawnPos;
	result->setPosition(vSpawnPos[gFunc::rndInt(0, vSpawnPos.size() - 1)]);

	return result;
}

enemyBase * enemyFactory::recycleEnemy(int type)
{
	enemyBase* result = nullptr;

	auto & lists = SGT_GAME->getSet().field->getList();
	auto & vEnemyList = lists.vEnemy;
	enemyBase** viewEnemy = nullptr;
	for (auto & i : vEnemyList)
	{
		if (gDigit::chk(i->getInfoCharacter().status, DIGIT::CHAR::DEAD) &&
			i->refEnemyType() == type)
		{
			viewEnemy = &i;
			break;
		}
	}

	if (viewEnemy)
	{
		enemyBase* & recycleable = *viewEnemy;

		auto & grape = SGT_GAME->getSet().field->getMember().grape;
		grape->pickData(recycleable, 2, recycleable->getPosition(), recycleable->getInfoCharacter().colRadius);

		recycleable->setPosition(lists.vSpawnPos[gFunc::rndInt(0, lists.vSpawnPos.size() - 1)]);
		recycleable->getInfoCharacter().nowHp = recycleable->getInfoCharacter().maxHp;
		recycleable->getInfoCharacter().status = 0;

		grape->putData(recycleable, 2, recycleable->getPosition(), recycleable->getInfoCharacter().colRadius);

		result = recycleable;
	}
	else
	{
		result = SGT_GAME->addEnemy(type);
	}

	int evType = EVENT::TYPE::ENEMY | EVENT::ACT::ENEMY::RESURRECTION;
	if (DIGIT_CHK(DIGIT::ENEMY::TANK))			evType |= EVENT::KIND::ENEMY::TANKER;
	else if (DIGIT_CHK(DIGIT::ENEMY::COMMON))	evType |= EVENT::KIND::ENEMY::BASE;

	MN_EVENT->add(new eventBase(result, nullptr, evType));

	return result;
}
