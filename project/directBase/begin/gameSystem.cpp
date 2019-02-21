#include "gameSystem.h"

#include "maptool_render.h"
#include "inGame_io.h"
#include "inGame_field.h"

#include "player.h"

#include "enemyBase.h"

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
	auto & vEnemyList = field->getList().vEnemy;
	vEnemyList.resize(1, nullptr);

	
}

enemyBase * gameSystem::addEnemy(int enemyType)
{
	enemyBase* result = nullptr;

	auto & vEnemyList = _set.field->getList().vEnemy;


	return nullptr;
}
