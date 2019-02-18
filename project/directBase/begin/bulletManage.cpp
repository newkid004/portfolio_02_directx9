#include "bulletManage.h"
#include "gFunc.h"

bulletManage::bulletManage(void)
{
}

bulletManage::~bulletManage(void)
{
}

void bulletManage::update(void)
{
	for (int i = 0; i < _vBullet.size(); ++i)
	{
		_vBullet[i]->getSpeed();
	}
}

void bulletManage::addBullet(const D3DXVECTOR3 & position, const D3DXVECTOR3 & forwardDir, float speed,
	bulletBase::EBulletType type)
{
	switch (type)
	{
	case bulletBase::EBulletType::B_RIFLE: case bulletBase::EBulletType::B_FIST:
	{
		bulletBase* bullet = new bulletBase(speed, type);
		bullet->setRay(position, forwardDir);
		_vBullet.push_back(bullet);
		break;
	}
	case bulletBase::EBulletType::B_SHOTGUN:
	{
		for (int i = 0; i < BULLET_MAX; ++i)
		{
			bulletBase* bullet = new bulletBase(speed, type);
			D3DXVECTOR3 dir = D3DXVECTOR3(forwardDir.x - (i - 6) * 0.5 + gFunc::rndFloat(-0.2f, 0.2f),
				forwardDir.y + gFunc::rndFloat(-1.0f, 1.0f),
				forwardDir.z);
			bullet->setRay(position, dir);
			_vBullet.push_back(bullet);
		}
		break;
	}
	}
}

void bulletManage::eraseBullet(int index)
{
}