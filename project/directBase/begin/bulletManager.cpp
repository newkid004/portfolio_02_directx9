#include "bulletManager.h"
#include "gFunc.h"

#include "characterBase.h"
#include "weaponBase.h"

bulletManager::bulletManager(void)
{
}

bulletManager::~bulletManager(void)
{
	std::list<gunBullet*>::iterator gunIter = _vGunBulletList.begin();
	std::list<fistBullet*>::iterator fistIter = _vFistBulletList.begin();
	for (; gunIter != _vGunBulletList.end(); ++gunIter)
	{
		SAFE_DELETE(*gunIter);
	}

	for (; fistIter != _vFistBulletList.end(); ++fistIter)
	{
		SAFE_DELETE(*fistIter);
	}
}

void bulletManager::update(void)
{
	std::list<gunBullet*>::iterator gunIter = _vGunBulletList.begin();
	std::list<fistBullet*>::iterator fistIter = _vFistBulletList.begin();
	for (; gunIter != _vGunBulletList.end();)
	{
		(*gunIter)->update();

		if (gFunc::Vec3Distance(D3DXVECTOR3(0, 0, 0), (*gunIter)->getPosition()) > 200)
		{
			SAFE_DELETE((*gunIter));
			gunIter = _vGunBulletList.erase(gunIter);
		}
		else
		{
			++gunIter;
		}
	}

	for (; fistIter != _vFistBulletList.end();)
	{
		(*fistIter)->update();
		if ((*fistIter)->getTime() < 0.0f)
		{
			SAFE_DELETE(*fistIter);
			fistIter = _vFistBulletList.erase(fistIter);
		}
		else
		{
			++fistIter;
		}
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

void bulletManager::addBullet(const D3DXVECTOR3 & position, const D3DXVECTOR3 & forwardDir, float speed,
	characterBase* bind)
{
	switch (bind->getWeapon()->getInfoWeapon().type)
	{
	case weapon_set::type::rifle: 
	{
		gunBullet* bullet = new gunBullet(speed, bind);
		bullet->setRay(position, forwardDir);
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
			_vGunBulletList.push_back(bullet);
		}
	} break;

	case weapon_set::type::normal:
	case weapon_set::type::zombie:
	case weapon_set::type::tank:
	{
		fistBullet* bullet = new fistBullet(speed, bind);
		bullet->setRay(position, forwardDir);
		bullet->setRange();
		_vFistBulletList.push_back(bullet);
	} break;

	}
}