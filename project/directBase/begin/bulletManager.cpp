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
				// UNVISIBLE BULLET DELETE
				SAFE_DELETE((*_gunIter));
				_gunIter = _vGunBulletList.erase(_gunIter);
				if (_gunIter == _vGunBulletList.end()) continue;

				// VISIBLE BULLET DELETE
				SAFE_DELETE((*_gunIter));
				_gunIter = _vGunBulletList.erase(_gunIter);
				if (_gunIter == _vGunBulletList.end()) continue;
			}
		
			if (gFunc::Vec3Distance(D3DXVECTOR3(0, 0, 0), (*_gunIter)->getPosition()) > 200)
			{
				// UNVISIBLE BULLET DELETE
				SAFE_DELETE((*_gunIter));
				_gunIter = _vGunBulletList.erase(_gunIter);
				if (_gunIter == _vGunBulletList.end()) continue;

				// VISIBLE BULLET DELETE
				SAFE_DELETE((*_gunIter));
				_gunIter = _vGunBulletList.erase(_gunIter);
				if (_gunIter == _vGunBulletList.end()) continue;
			}
			else ++_gunIter;
		}
		else ++_gunIter;
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
		if((*gunIter)->getBulletType() == bulletBase::TYPE::VISIBLE)
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

				// ������
				D3DXVECTOR3 intersect = ray.origin + info.distance * ray.direction;
				MN_SND->find("shootWall")->play(gFunc::getSoundVolumeToPlayer(mapObj[i]->getPosition()),
					gFunc::rndFloat(0.8f, 1.0f));
				//printf("�� �浹!! intersect point : %f, %f, %f\n", intersect.x, intersect.y, intersect.z);
				bullet->setIntersect(intersect);
				MN_EVENT->add(new eHitWallBullet(bullet, mapObj[i]));

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
			auto & enemy = (*enemyIter);
			auto & mBoundBoxSet = enemy->getBoundingBoxSetList();
			auto & mBoundSphereSet = enemy->getBoundingSphereSetList();
			auto mSphere = enemy->getBoundingSphere();
			
			mSphere.center += enemy->getBoundingSphereOffset();
			mSphere.radius *= enemy->getOriginMesh()->getScale().x;
			
			D3DXVECTOR3 intersect;

				
			if (pick::isLine2Sphere(&bullet->getRay(), &intersect,
				bullet->getSpeed(), mSphere))
			{
				for (auto rValue : mBoundSphereSet)
				{
					auto sphere = rValue.second.sphere;
					sphere.center = rValue.second.drawPosition;
					sphere.radius *= enemy->getOriginMesh()->getScale().x * 40;
				
					if (pick::isLine2Sphere(&bullet->getRay(), &intersect,
						bullet->getSpeed(), sphere))
					{
						//printf("ĳ�� %s �浹!! %d\n", rValue.first.c_str(), (int)(*enemyIter));
						//printf("ĳ�� %d �浹!!\n", (int)(*enemyIter));
						
						// �浹 ���� ��Ʈ
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

	// ��ü : ENEMY, ��� : PLAYER
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
			D3DXVECTOR3 zombie2Player = _bindPlayer->getPosition() - bullet->getRay().origin;
			float cosAngle = D3DXVec3Dot(&bullet->getRay().direction, &zombie2Player);
					
			if (cosAngle < 0.0f) return false;

			if(!MN_SND->find("hitbyEnemey")->isPlaySound())	MN_SND->find("hitbyEnemey")->play(-1.0f, gFunc::rndFloat(0.7f, 1.0f));
			MN_SND->find("hit_punch")->play(-1.0f, gFunc::rndFloat(0.7f, 1.0f));

			//printf("�ǰ�!! �ǰ� ��� : %d     %d\n", 
			//bullet->getWeaponType(),
			//rand() % 100);

			// �浹 �� �̺�Ʈ ó��
			// {
			MN_EVENT->add(new eHitCharacterBullet(bullet, SGT_GAME->getSet().player, 0));
			// }

			return true;
		}
	}
	else
	{
		// ��ü : PLAYER, ��� : ENEMY
		std::vector<enemyBase *>::iterator enemyIter;
		auto & vEnemyList = SGT_GAME->getSet().field->getList().vEnemy;

		for (enemyIter = vEnemyList.begin(); enemyIter != vEnemyList.end();)
		{
			auto & enemy = (*enemyIter);
			auto & mBoundBoxSet = enemy->getBoundingBoxSetList();
			auto & mBoundSphereSet = enemy->getBoundingSphereSetList();
			auto mSphere = enemy->getBoundingSphere();

			mSphere.center += enemy->getBoundingSphereOffset();
			mSphere.radius *= enemy->getOriginMesh()->getScale().x;

			D3DXVECTOR3 intersect;

			if (pick::isLine2Sphere(&bullet->getRay(), &intersect,
				bullet->getSpeed(), mSphere))
			{
				for (auto rValue : mBoundSphereSet)
				{
					auto sphere = rValue.second.sphere;
					sphere.center = rValue.second.drawPosition;
					sphere.radius *= enemy->getOriginMesh()->getScale().x * 40;

					if (pick::isLine2Sphere(&bullet->getRay(), &intersect,
						bullet->getSpeed(), sphere))
					{
						MN_SND->find("hitEnemy")->play(-1.0f, gFunc::rndFloat(0.8f, 1.0f));
						//printf("���� �������� %s �浹!! %d\n", rValue.first.c_str(), rand() % 100);

						// �浹 ���� ��Ʈ
						int hitPart = _oPartList.find(rValue.first)->second;

						MN_EVENT->add(new eHitCharacterBullet(bullet, *enemyIter, hitPart));
						gDigit::put((*enemyIter)->getInfoCharacter().status, inGame_digit::CHAR::SHOVED);

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
		for (int i = 0; i < SHOTGUN_MAX; ++i)
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