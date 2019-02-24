#include "enemyFactory.h"

#include "managerList.h"
#include "gFunc.h"
#include "gDigit.h"

#include "eventBase.h"
#include "eventDef.h"

#include "aStar_path.h"

#include "inGame_digit.h"
#include "inGame_field.h"
#include "inGame_grape.h"

#include "enemyBase.h"
#include "nodeMesh.h"
#include "patternMesh.h"

#include "controllerBase.h"

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
		int look = gFunc::rndInt(0, 1);

		switch (look)
		{
		case 0: result = new enemyBase(MN_SRC->getPatternMesh("enemy_male_0"));		break;
		case 1: result = new enemyBase(MN_SRC->getPatternMesh("enemy_female_0"));	break;
		}

		auto & origin = result->getOriginMesh();

		origin->setupBoneInfo("ValveBiped_Bip01_Head1", 9, 9, 9);
		origin->setupBoneInfo("ValveBiped_Bip01_Spine1", 14, 18, 10);
		origin->setupBoneInfo("ValveBiped_Bip01_L_Foot", 8, 8, 8);
		origin->setupBoneInfo("ValveBiped_Bip01_R_Foot", 8, 8, 8);
		origin->setupBoneInfo("ValveBiped_Bip01_L_Calf", 9, 9, 9);
		origin->setupBoneInfo("ValveBiped_Bip01_R_Calf", 9, 9, 9);
		origin->setupBoneInfo("ValveBiped_Bip01_L_Thigh", 9, 9, 9);
		origin->setupBoneInfo("ValveBiped_Bip01_R_Thigh", 9, 9, 9);
		origin->setupBoneInfo("ValveBiped_Bip01_L_Hand", 8, 8, 8);
		origin->setupBoneInfo("ValveBiped_Bip01_R_Hand", 8, 8, 8);
		origin->setupBoneInfo("ValveBiped_Bip01_L_Forearm", 8, 8, 8);
		origin->setupBoneInfo("ValveBiped_Bip01_R_Forearm", 8, 8, 8);
		origin->setupBoneInfo("ValveBiped_Bip01_L_UpperArm", 7, 7, 7);
		origin->setupBoneInfo("ValveBiped_Bip01_R_UpperArm", 7, 7, 7);

		origin->init();
		origin->setDebugEnable(true, EDebugDrawType::SPHERE);
	}
	auto & vSpawnPos = SGT_GAME->getSet().field->getList().vSpawnPos;
	auto & sp = vSpawnPos[gFunc::rndInt(0, vSpawnPos.size() - 1)];
	result->setPosition(sp->getPosition() +
		D3DXVECTOR3(
			gFunc::rndFloat(-sp->getPlaneRadius(), sp->getPlaneRadius()),
			gFunc::rndFloat(-sp->getPlaneRadius(), sp->getPlaneRadius()),
			gFunc::rndFloat(-sp->getPlaneRadius(), sp->getPlaneRadius()))
	);
	result->getInfoMove().maximumSpeed = 0.32f;

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
		
		auto & viewSpawner = lists.vSpawnPos[gFunc::rndInt(0, lists.vSpawnPos.size() - 1)];
		
		recycleable->setPosition(viewSpawner->getPosition() +
			D3DXVECTOR3(
				gFunc::rndFloat(-viewSpawner->getPlaneRadius(), viewSpawner->getPlaneRadius()),
				gFunc::rndFloat(-viewSpawner->getPlaneRadius(), viewSpawner->getPlaneRadius()),
				gFunc::rndFloat(-viewSpawner->getPlaneRadius(), viewSpawner->getPlaneRadius()))
		);
		recycleable->getInfoCharacter().nowHp = recycleable->getInfoCharacter().maxHp;
		recycleable->getInfoCharacter().status = 0;

		grape->putData(recycleable, 2, recycleable->getPosition(), recycleable->getInfoCharacter().colRadius);
		SAFE_DELETE(recycleable->getController()->getPath());

		result = recycleable;
	}
	else
	{
		if (vEnemyList.size() < SGT_GAME->getStatus().numMaximumEnemy)
			result = SGT_GAME->addEnemy(type);
	}

	int evType = EVENT::TYPE::ENEMY | EVENT::ACT::ENEMY::RESURRECTION;
	if (DIGIT_CHK(DIGIT::ENEMY::TANK))			evType |= EVENT::KIND::ENEMY::TANKER;
	else if (DIGIT_CHK(DIGIT::ENEMY::COMMON))	evType |= EVENT::KIND::ENEMY::BASE;

	MN_EVENT->add(new eventBase(result, nullptr, evType));

	return result;
}
