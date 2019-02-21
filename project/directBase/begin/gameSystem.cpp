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

#include "bulletManager.h"
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
	_set.enemy->update();

	collision();
}

void gameSystem::draw(void)
{
	_set.field->draw();
	_set.player->draw();
	_set.enemy->draw();
}

void gameSystem::initField(void)
{
	auto & field = _set.field;
	
	field = inGame_io::createField2File(0);
	
	// enemy
	auto & vEnemyList = field->getList().vEnemy;
	vEnemyList.resize(1, nullptr);

}

void gameSystem::collision(void)
{
	auto & vBulletList = GET_BULLET_MANAGER()->getGunBulletList();
	
	vector<gunBullet *>::iterator iter;

	for (iter = vBulletList.begin(); iter != vBulletList.end();)
	{
		auto mapObj = _set.field->getList().vWall;
		auto ray = (*iter)->getRay();

		for (int i = 0; i < mapObj.size(); ++i)
		{
			auto wall = mapObj[i]->getMeshSet()->mesh;
			auto box = mapObj[i]->getBoundingBoxList()[0];
			mapObj[i]->getBoundingBoxFinal(&box);

			if (pick::isLine2Box(&ray, (*iter)->getSpeed(), box))
			{
				pick::info info;
				ZeroMemory(&info, sizeof(info));
				pick::applyMatrix(&ray, &ray, &mapObj[i]->getMatrixFinal());

				if (pick::chkPick(&info, &ray, wall))
				{
					D3DXMATRIXA16 matrix = mapObj[i]->getMatrixFinal();
					D3DXMatrixInverse(&matrix, NULL, &matrix);
					pick::applyMatrix(&ray, &ray, &matrix);
					D3DXVECTOR3 intersect = ray.origin + info.distance * ray.direction;

					printf("º® Ãæµ¹!! intersect point : %f, %f, %f\n", intersect.x, intersect.y, intersect.z);
					SAFE_DELETE((*iter));
					iter = vBulletList.erase(iter);
					if (vBulletList.size() == 0)
					{
						return;
					}
					continue;
				}
			}
		}
		if(iter != vBulletList.end())
			++iter;
	}


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
