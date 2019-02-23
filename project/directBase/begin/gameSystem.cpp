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
#define FLAGPOSITION 0.16 / 1015.227

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

	collision();
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
}

void gameSystem::collision(void)
{
	auto & vBulletList = GET_BULLET_MANAGER()->getGunBulletList();

	if (vBulletList.size() > 2)
	{
		int n = 0;
	}
	list<gunBullet *>::iterator bulletIter;
	vector<enemyBase *>::iterator enemyIter;

	for (bulletIter = vBulletList.begin(); bulletIter != vBulletList.end();)
	{
		// WALL
		auto & mapObj = _set.map->getMapList();
		auto ray = (*bulletIter)->getRay();

		for (int i = 0; i < mapObj.size(); ++i)
		{
			auto wall = mapObj[i]->getMeshSet()->mesh;
			auto box = mapObj[i]->getBoundingBoxList()[0];
			mapObj[i]->getBoundingBoxFinal(&box);
		
			if (pick::isLine2Box(&ray, (*bulletIter)->getSpeed(), box))
			{
				pick::info info;
				ZeroMemory(&info, sizeof(info));
				pick::applyMatrix(&ray, &ray, &mapObj[i]->getMatrixFinal());
		
				if (pick::chkPick(&info, &ray, wall))
				{
					D3DXMATRIXA16 matrix = mapObj[i]->getMatrixFinal();
					D3DXMatrixInverse(&matrix, NULL, &matrix);
					pick::applyMatrix(&ray, &ray, &matrix);

					// 교차점
					D3DXVECTOR3 intersect = ray.origin + info.distance * ray.direction;
		
					printf("벽 충돌!! intersect point : %f, %f, %f\n", intersect.x, intersect.y, intersect.z);
					bulletIter = vBulletList.erase(bulletIter);

					if (bulletIter == vBulletList.end())
					{
						return;
					}
				}
			}
		}

		// ENEMY
		auto & field = _set.field;
		auto & vEnemyList = field->getList().vEnemy;
		for (enemyIter = vEnemyList.begin(); enemyIter != vEnemyList.end();)
		{
			auto & enemy = (*enemyIter)->getOriginMesh();
			auto & mBoundBoxSet = enemy->getBoundingBoxSetList();
			auto & mBoundSphereSet = enemy->getBoundingSphereSetList();
			auto mSphere = enemy->getBoundingSphere();

			mSphere.center += enemy->getBoundingSphereOffset();
			mSphere.radius *= enemy->getScale().x;

			D3DXVECTOR3 intersect;

			if (pick::isLine2Sphere(&(*bulletIter)->getRay(), &intersect,
				(*bulletIter)->getSpeed(), mSphere))
			{
				for (auto rValue : mBoundSphereSet)
				{
					auto sphere = rValue.second.sphere;
					sphere.center = rValue.second.drawPosition;
					sphere.radius *= enemy->getScale().x * 40;
				
					if (pick::isLine2Sphere(&(*bulletIter)->getRay(), &intersect,
						(*bulletIter)->getSpeed(), sphere))
					{
						//printf("캐릭 충돌!! %d, intersect point : %f, %f, %f\n%s\n", rand() % 100, intersect2.x, intersect2.y, intersect2.z, rValue.first.c_str());
						printf("캐릭 %s 충돌!! %d\n", rValue.first.c_str(), rand() % 100);

						SAFE_DELETE((*bulletIter));
						bulletIter = vBulletList.erase(bulletIter);

						if (bulletIter == vBulletList.end())
						{
							return;
						}
						
					}
				}
			}
			++enemyIter;
			
		}
		if (vBulletList.size() != 0)
		{
			++bulletIter;
		}
		else
		{
			return;
		}
	}


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
	origin->setupBoneInfo("ValveBiped_Bip01_L_Forearm",  8, 8, 8);
	origin->setupBoneInfo("ValveBiped_Bip01_R_Forearm",  8, 8, 8);
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
