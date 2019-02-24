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
	_set.map->init();

	D3DXVECTOR3 centerPos(0, 0, 0);
	auto grape = field->getMember().grape;
	for (auto & i : _set.map->getMapList())
	{
		D3DXVECTOR3 boxPos = i->getBoundingBoxList()[0].min;
		i->calMatrixFinal();
		D3DXVec3TransformCoord(&boxPos, &boxPos, &i->getMatrixFinal());
		float radius = gFunc::Vec3Distance(centerPos, boxPos);
		grape->putData(i, 0, i->getPosition(), radius);
	}
}

enemyBase * gameSystem::addEnemy(int enemyType)
{
	enemyBase* result = enemyFactory::createEnemy(enemyType);

	auto & listSet = _set.field->getList();

	auto & vTotal = listSet.vTotalObject;
	auto & vEnemyList = listSet.vEnemy;
	auto & vUpdateList = listSet.vUpdateable;
	auto & vRenderable = listSet.vRenderable;

	_set.field->getMember().grape->putData(result, 2, result->getPosition(), result->getInfoCharacter().colRadius);
	vTotal.push_back(result);
	vEnemyList.push_back(result);
	vUpdateList.push_back(result);
	vRenderable.push_back(result);

	int evType = EVENT::TYPE::ENEMY | EVENT::ACT::ENEMY::ADDED;
	if (gDigit::chk(inGame_digit::ENEMY::TANK, enemyType))			gDigit::put(evType, EVENT::KIND::ENEMY::TANKER);
	else if (gDigit::chk(inGame_digit::ENEMY::COMMON, enemyType))	gDigit::put(evType, EVENT::KIND::ENEMY::BASE);

	MN_EVENT->add(new eventBase(result, nullptr, evType));
	
	return result;
}
