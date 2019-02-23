#include "gameSystem.h"

#include "managerList.h"
#include "gDigit.h"

#include "gFunc.h"
#include "pickRay.h"
#include "maptool_render.h"
#include "inGame_io.h"
#include "inGame_field.h"
#include "inGame_grape.h"
#include "inGame_digit.h"

#include "player.h"

#include "enemyBase.h"
#include "enemyFactory.h"
#include "patternMesh.h"

#include "eventBase.h"

#include "mapObject.h"
#include "bulletManager.h"

gameSystem::gameSystem()
{
	_set.map_render = new maptool_render();
	_set.map = new mapObject();
	initField();
}

gameSystem::~gameSystem()
{
	SAFE_DELETE(_set.map_render);
}

void gameSystem::update(void)
{
	_set.field->update();
	_set.player->update();
	_set.map->update();
}

void gameSystem::draw(void)
{
	_set.field->draw();
	_set.player->draw();
	_set.map->draw();
}

void gameSystem::initField(void)
{
	auto & field = _set.field;
	
	field = inGame_io::createField2File(0);
	
	// enemy
	auto & vEnemyList = field->getList().vEnemy;

	// map
	//D3DXVECTOR3 centerPos(0, 0, 0);
	//auto grape = field->getMember().grape;
	//_set.map->init();
	//for (auto & i : _set.map->getMapList())
	//{
	//	D3DXVECTOR3 boxPos = i->getBoundingBoxList()[0].min;
	//	float radius = gFunc::Vec3Distance(centerPos, boxPos);
	//	grape->putData(i, 0, i->getPosition(), radius);
	//}
}

enemyBase * gameSystem::addEnemy(int enemyType)
{
	auto & listSet = _set.field->getList();

	auto & vTotal = listSet.vTotalObject;
	auto & vEnemyList = listSet.vEnemy;
	auto & vUpdateList = listSet.vUpdateable;
	auto & vRenderable = listSet.vRenderable;
	enemyBase* result = enemyFactory::createEnemy(enemyType);
	auto & origin = result->getOriginMesh();

	origin->setupBoneInfo("ValveBiped_Bip01_Head1",		 9, 9, 9);
	origin->setupBoneInfo("ValveBiped_Bip01_Spine1",	 14, 18, 10);
	origin->setupBoneInfo("ValveBiped_Bip01_L_Foot",	 8, 8, 8);
	origin->setupBoneInfo("ValveBiped_Bip01_R_Foot",	 8, 8, 8);
	origin->setupBoneInfo("ValveBiped_Bip01_L_Calf",	 9, 9, 9);
	origin->setupBoneInfo("ValveBiped_Bip01_R_Calf",	 9, 9, 9);
	origin->setupBoneInfo("ValveBiped_Bip01_L_Thigh",	 9, 9, 9);
	origin->setupBoneInfo("ValveBiped_Bip01_R_Thigh",	 9, 9, 9);
	origin->setupBoneInfo("ValveBiped_Bip01_L_Hand",	 8, 8, 8);
	origin->setupBoneInfo("ValveBiped_Bip01_R_Hand",	 8, 8, 8);
	origin->setupBoneInfo("ValveBiped_Bip01_L_Forearm",	 8, 8, 8);
	origin->setupBoneInfo("ValveBiped_Bip01_R_Forearm",	 8, 8, 8);
	origin->setupBoneInfo("ValveBiped_Bip01_L_UpperArm", 7, 7, 7);
	origin->setupBoneInfo("ValveBiped_Bip01_R_UpperArm", 7, 7, 7);

	origin->init();
	origin->setDebugEnable(true, EDebugDrawType::SPHERE);

	_set.field->getMember().grape->putData(result, 2, result->getPosition(), result->getInfoCharacter().colRadius);
	vTotal.push_back(result);
	vEnemyList.push_back(result);
	vUpdateList.push_back(result);
	vRenderable.push_back(result);

	int evType = EVENT::TYPE::ENEMY | EVENT::ACT::ENEMY::ADDED;
	if (gDigit::chk(inGame_digit::ENEMY::TANK, enemyType))			evType |= EVENT::KIND::ENEMY::TANKER;
	else if (gDigit::chk(inGame_digit::ENEMY::COMMON, enemyType))	evType |= EVENT::KIND::ENEMY::BASE;

	MN_EVENT->add(new eventBase(result, nullptr, evType));

	return result;
}
