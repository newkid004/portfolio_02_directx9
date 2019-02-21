#include "bulletManager.h"
#include "gFunc.h"

bulletManager::bulletManager(void)
{
}

bulletManager::~bulletManager(void)
{
	for (int i = 0; i < _vGunBulletList.size(); ++i)
	{
		SAFE_DELETE(_vGunBulletList[i]);
	}

	for (int i = 0; i < _vFistBulletList.size(); ++i)
	{
		SAFE_DELETE(_vFistBulletList[i]);
	}
}

void bulletManager::update(void)
{
	std::vector<gunBullet*>::iterator iter = _vGunBulletList.begin();
	for (;iter != _vGunBulletList.end();)
	{
		(*iter)->update();

		if (gFunc::Vec3Distance(D3DXVECTOR3(0, 0, 0), (*iter)->getPosition()) > 200)
		{
			SAFE_DELETE((*iter));
			iter = _vGunBulletList.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	for (int i = 0; i < _vFistBulletList.size(); ++i)
	{
		_vFistBulletList[i]->update();
	}


}

void bulletManager::draw(void)
{
	for (int i = 0; i < _vGunBulletList.size(); ++i)
	{
		_vGunBulletList[i]->draw();
	}
}

void bulletManager::addBullet(const D3DXVECTOR3 & position, const D3DXVECTOR3 & forwardDir, float speed,
	bulletBase::EBulletType type)
{
	switch (type)
	{
	case bulletBase::EBulletType::B_RIFLE: 
	{
		gunBullet* bullet = new gunBullet(speed, type);
		bullet->setRay(position, forwardDir);
		_vGunBulletList.push_back(bullet);
		break;
	}
	case bulletBase::EBulletType::B_SHOTGUN:
	{
		for (int i = 0; i < BULLET_MAX; ++i)
		{
			gunBullet* bullet = new gunBullet(speed, type);
			D3DXVECTOR3 dir = D3DXVECTOR3(forwardDir.x + gFunc::rndFloat(-0.13f, 0.13f),
				forwardDir.y + gFunc::rndFloat(-0.08f, 0.08f),
				forwardDir.z);
			bullet->setRay(position, dir);
			_vGunBulletList.push_back(bullet);
		}
		break;
	}
	case bulletBase::EBulletType::B_FIST:
	{
		fistBullet* bullet = new fistBullet(speed, type);
		bullet->setRay(position, forwardDir);
		bullet->setRange();
		_vFistBulletList.push_back(bullet);
		break;
	}
	}
}

void bulletManager::eraseGunBullet(int index)
{
	SAFE_DELETE(_vGunBulletList[index]);
	_vGunBulletList.erase(_vGunBulletList.begin() + index);
}

void bulletManager::eraseFistBullet(int index)
{
	SAFE_DELETE(_vFistBulletList[index]);
	_vFistBulletList.erase(_vFistBulletList.begin() + index);
}