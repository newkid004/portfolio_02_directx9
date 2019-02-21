#include "gameSystem.h"

#include "managerList.h"
#include "gDigit.h"

#include "maptool_render.h"
#include "inGame_io.h"
#include "inGame_field.h"
#include "inGame_grape.h"
#include "inGame_digit.h"

#include "player.h"

#include "enemyBase.h"
#include "enemyFactory.h"

#include "eventBase.h"

gameSystem::gameSystem()
{
	_set.map_render = new maptool_render();

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
}

void gameSystem::draw(void)
{
	_set.field->draw();
	_set.player->draw();
}

void gameSystem::initField(void)
{
	auto & field = _set.field;
	
	field = inGame_io::createField2File(0);
	
	// enemy
	addEnemy();
}

enemyBase * gameSystem::addEnemy(int enemyType)
{
	auto & vEnemyList = _set.field->getList().vEnemy;
	enemyBase* result = enemyFactory::createEnemy(enemyType);

	_set.field->getMember().grape->putData(result, 2, result->getPosition(), result->getInfoCharacter().colRadius);
	vEnemyList.push_back(result);

	int evType = EVENT::TYPE::ENEMY | EVENT::ACT::ENEMY::ADDED;
	if (gDigit::chk(inGame_digit::ENEMY::TANK, enemyType))			evType |= EVENT::KIND::ENEMY::TANKER;
	else if (gDigit::chk(inGame_digit::ENEMY::COMMON, enemyType))	evType |= EVENT::KIND::ENEMY::BASE;

	MN_EVENT->add(new eventBase(result, nullptr, evType));

	return result;
}
