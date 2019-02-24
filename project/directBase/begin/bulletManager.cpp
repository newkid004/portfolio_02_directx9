#include "bulletManager.h"
#include "gFunc.h"
#include "gDigit.h"
#include "managerList.h"
#include "inGame_field.h"
#include "inGame_digit.h"
#include "enemyBase.h"
#include "patternMesh.h"
#include "mapObject.h"
#include "characterBase.h"
#include "player.h"
#include "weaponBase.h"
#include "eventBase.h"

#include "eHitBullet.h"

using namespace std;


bulletManager::bulletManager(void)
{
	_oPartList.insert(make_pair("ValveBiped_Bip01_Head1", inGame_digit::PART::HEAD));
	_oPartList.insert(make_pair("ValveBiped_Bip01_Spine1", inGame_digit::PART::MIDDLE));
	_oPartList.insert(make_pair("ValveBiped_Bip01_L_Foot", inGame_digit::PART::NONE));
	_oPartList.insert(make_pair("ValveBiped_Bip01_R_Foot", inGame_digit::PART::NONE));
	_oPartList.insert(make_pair("ValveBiped_Bip01_L_Calf", inGame_digit::PART::NONE));
	_oPartList.insert(make_pair("ValveBiped_Bip01_R_Calf", inGame_digit::PART::NONE));
	_oPartList.insert(make_pair("ValveBiped_Bip01_L_Thigh", inGame_digit::PART::MIDDLE));
	_oPartList.insert(make_pair("ValveBiped_Bip01_R_Thigh", inGame_digit::PART::MIDDLE));
	_oPartList.insert(make_pair("ValveBiped_Bip01_L_Hand", inGame_digit::PART::RIGHT));
	_oPartList.insert(make_pair("ValveBiped_Bip01_R_Hand", inGame_digit::PART::LEFT));
	_oPartList.insert(make_pair("ValveBiped_Bip01_L_Forearm", inGame_digit::PART::RIGHT));
	_oPartList.insert(make_pair("ValveBiped_Bip01_R_Forearm", inGame_digit::PART::LEFT));
	_oPartList.insert(make_pair("ValveBiped_Bip01_L_UpperArm", inGame_digit::PART::RIGHT));
	_oPartList.insert(make_pair("ValveBiped_Bip01_R_UpperArm", inGame_digit::PART::LEFT));
}

bulletManager::~bulletManager(void)
{
	_gunIter = _vGunBulletList.begin();
	_fistIter = _vFistBulletList.begin();
	for (; _gunIter != _vGunBulletList.end(); ++_gunIter)
	{
		SAFE_DELETE(*_gunIter);
	}

	for (; _fistIter != _vFistBulletList.end(); ++_fistIter)
	{
		SAFE_DELETE(*_fistIter);
	}
}

void bulletManager::init(void)
{
}

void bulletManager::update(void)
{
	_gunIter = _vGunBulletList.begin();
	_fistIter = _vFistBulletList.begin();
	for (; _gunIter != _vGunBulletList.end();)
	{
		(*_gunIter)->update();

		if((*_gunIter)->getBulletType() == bulletBase::TYPE::UNVISIBLE)
		{
			if (gunCollision(*_gunIter))
			{
				SAFE_DELETE((*_gunIter));
				_gunIter = _vGunBulletList.erase(_gunIter);
				SAFE_DELETE((*_gunIter));
				_gunIter = _vGunBulletList.erase(_gunIter);
				if (_gunIter == _vGunBulletList.end()) continue;
			}
		
			if (gFunc::Vec3Distance(D3DXVECTOR3(0, 0, 0), (*_gunIter)->getPosition()) > 200)
			{
				SAFE_DELETE((*_gunIter));
				_gunIter = _vGunBulletList.erase(_gunIter);
				SAFE_DELETE((*_gunIter));
				_gunIter = _vGunBulletList.erase(_gunIter);
			}
			else ++_gunIter;
		}
	}

	for (; _fistIter != _vFistBulletList.end();)
	{
		(*_fistIter)->update();

		if (fistCollision(*_fistIter))
		{
			SAFE_DELETE(*_fistIter);
			_fistIter = _vFistBulletList.erase(_fistIter);

			if (_fistIter == _vFistBulletList.end()) continue;
		}

		if ((*_fistIter)->getTime() < 0.0f)
		{
			SAFE_DELETE(*_fistIter);
			_fistIter = _vFistBulletList.erase(_fistIter);
		}
		else ++_fistIter;
		
	}


}

void bulletManager::draw(void)
{
	std::list<gunBullet*>::iterator gunIter = _vGunBulletList.begin();

	for (; gunIter != _vGunBulletList.end(); ++gunIter)
	{
		(*gunIter)->draw();
	}
}

bool bulletManager::gunCollision(gunBullet * bullet)
{
	// WALL
	auto & mapObj = SGT_GAME->getSet().map->getMapList();
	auto ray = bullet->getRay();

	for (int i = 0; i < mapObj.size(); ++i)
	{
		auto wall = mapObj[i]->getMeshSet()->mesh;
		auto box = mapObj[i]->getBoundingBoxList()[0];
		mapObj[i]->getBoundingBoxFinal(&box);

		if (pick::isLine2Box(&ray, bullet->getSpeed(), box))
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
				
				return true;
			}
		}
	}

	// ENEMY
	std::vector<enemyBase *>::iterator enemyIter;
	auto & vEnemyList = SGT_GAME->getSet().field->getList().vEnemy;
	for (enemyIter = vEnemyList.begin(); enemyIter != vEnemyList.end();)
	{
		if (!gDigit::chk((*enemyIter)->getInfoCharacter().status, inGame_digit::CHAR::DEAD))
		{
			auto & enemy = (*enemyIter)->getOriginMesh();
			auto & mBoundBoxSet = enemy->getBoundingBoxSetList();
			auto & mBoundSphereSet = enemy->getBoundingSphereSetList();
			auto mSphere = enemy->getBoundingSphere();

			mSphere.center += enemy->getBoundingSphereOffset();
			mSphere.radius *= enemy->getScale().x;

			D3DXVECTOR3 intersect;

			if (pick::isLine2Sphere(&bullet->getRay(), &intersect,
				bullet->getSpeed(), mSphere))
			{
				for (auto rValue : mBoundSphereSet)
				{
					auto sphere = rValue.second.sphere;
					sphere.center = rValue.second.drawPosition;
					sphere.radius *= enemy->getScale().x * 40;

					if (pick::isLine2Sphere(&bullet->getRay(), &intersect,
						bullet->getSpeed(), sphere))
					{
						printf("캐릭 %s 충돌!! %d\n", rValue.first.c_str(), rand() % 100);

						// 충돌 부위 파트
						int hitPart = _oPartList.find(rValue.first)->second;

						bullet->setIntersect(intersect);

						MN_EVENT->add(new eHitCharacterBullet(bullet, *enemyIter, hitPart));

						return true;
					}
				}
			}
		}
		if(enemyIter != vEnemyList.end()) ++enemyIter;
	}
	return false;
}

bool bulletManager::fistCollision(fistBullet * bullet)
{	
	if (_bindPlayer == nullptr) return false;

	auto player = _bindPlayer->getOriginMesh();
	// 주체 : ENEMY, 대상 : PLAYER
	if (bullet->getWeaponType() == weapon_set::type::zombie)
	{
		auto & mBoundSphereSet = player->getBoundingSphereSetList();
		auto mSphere = player->getBoundingSphere();

		mSphere.center += player->getBoundingSphereOffset();
		mSphere.radius *= player->getScale().x;

		D3DXVECTOR3 intersect;

		if (pick::isLine2Sphere(&bullet->getRay(), &intersect,
			bullet->getSpeed(), mSphere))
		{
			//for (auto rValue : mBoundSphereSet)
			//{
			//	auto sphere = rValue.second.sphere;
			//	sphere.center = rValue.second.drawPosition;
			//	sphere.radius *= _bindPlayer->getScale().x * 40;
			//
			//	if (pick::isLine2Sphere(&bullet->getRay(), &intersect,
			//		bullet->getSpeed(), sphere))
			//	{
			//		D3DXVECTOR3 zom2Player = _bindPlayer->getPosition() - bullet->getRay().origin;
			//		float cosAngle = D3DXVec3Dot(&bullet->getRay().direction, &zom2Player);
			//		
			//if (cosAngle < 0.0f)
			//{
			//	return false;
			//}

			printf("피격!! 피격 대상 : %d     %d\n", 
			bullet->getWeaponType(),
			rand() % 100);

			// 충돌 시 이벤트 처리
			// {

			// }

			return true;
				//}
			//}
		}
	}
	else
	{
		// 주체 : PLAYER, 대상 : ENEMY
		std::vector<enemyBase *>::iterator enemyIter;
		auto & vEnemyList = SGT_GAME->getSet().field->getList().vEnemy;

		for (enemyIter = vEnemyList.begin(); enemyIter != vEnemyList.end();)
		{
			auto & enemy = (*enemyIter)->getOriginMesh();
			auto & mBoundBoxSet = enemy->getBoundingBoxSetList();
			auto & mBoundSphereSet = enemy->getBoundingSphereSetList();
			auto mSphere = enemy->getBoundingSphere();

			mSphere.center += enemy->getBoundingSphereOffset();
			mSphere.radius *= enemy->getScale().x;

			D3DXVECTOR3 intersect;

			if (pick::isLine2Sphere(&bullet->getRay(), &intersect,
				bullet->getSpeed(), mSphere))
			{
				for (auto rValue : mBoundSphereSet)
				{
					auto sphere = rValue.second.sphere;
					sphere.center = rValue.second.drawPosition;
					sphere.radius *= enemy->getScale().x * 40;

					if (pick::isLine2Sphere(&bullet->getRay(), &intersect,
						bullet->getSpeed(), sphere))
					{
						printf("좀비 근접공격 %s 충돌!! %d\n", rValue.first.c_str(), rand() % 100);

						// 충돌 부위 파트
						int hitPart = _oPartList.find(rValue.first)->second;

						MN_EVENT->add(new eHitCharacterBullet(bullet, *enemyIter, hitPart));

						return true;
					}
				}
			}
			if (enemyIter != vEnemyList.end()) ++enemyIter;
		}
	}
	
	return false;
}

void bulletManager::addBullet(const D3DXVECTOR3 & position, const D3DXVECTOR3 & forwardDir, float speed,
	weaponBase* bind, bulletBase::TYPE type)
{
	switch (bind->getInfoWeapon().type)
	{
	case weapon_set::type::rifle: 
	{
		gunBullet* bullet = new gunBullet(speed, bind);
		bullet->setRay(position, forwardDir);
		bullet->setBulletType(type);
		_vGunBulletList.push_back(bullet);
	} break;

	case weapon_set::type::shotgun:
	{
		for (int i = 0; i < BULLET_MAX; ++i)
		{
			gunBullet* bullet = new gunBullet(speed, bind);
			D3DXVECTOR3 dir = D3DXVECTOR3(forwardDir.x + gFunc::rndFloat(-0.13f, 0.13f),
				forwardDir.y + gFunc::rndFloat(-0.08f, 0.08f),
				forwardDir.z);
			bullet->setRay(position, dir);
			bullet->setBulletType(type);
			_vGunBulletList.push_back(bullet);
		}
	} break;
	case weapon_set::type::none:
	case weapon_set::type::zombie:
	case weapon_set::type::tank:
	{
		fistBullet* bullet = new fistBullet(speed, bind);
		bullet->setRay(position, forwardDir);
		bullet->setBulletType(type);
		_vFistBulletList.push_back(bullet);
	} break;

	}
}