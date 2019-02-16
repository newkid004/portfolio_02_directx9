#include "bulletManager.h"
#include "gFunc.h"
#include "camera.h"
#include "managerList.h"

bulletManager::bulletManager()
{
}

bulletManager::~bulletManager()
{
	deleteBullet();
}

void bulletManager::update(void)
{
	for (int i = 0; i < m_vBulletList.size(); ++i)
	{
		m_vBulletList[i]->update();

		if (gFunc::Vec3Distance(D3DXVECTOR3(0,0,0), m_vBulletList[i]->getPosition()) > 100)
		{
			deleteBullet(i);
		}
	}
}

void bulletManager::draw(void)
{
	for (int i = 0; i < m_vBulletList.size(); ++i)
	{
		m_vBulletList[i]->draw();
	}
}

void bulletManager::addBullet(const D3DXVECTOR3 & origin, const D3DXVECTOR3 & direction, float speed)
{
	bullet* mBullet = new bullet(origin, direction, speed);

	m_vBulletList.push_back(mBullet);
}

void bulletManager::setPosition(int index, const D3DXVECTOR3 & position, bool onOff)
{
	m_vBulletList[index]->setIntersect(position);
	m_vBulletList[index]->setOnOff(onOff);
}

void bulletManager::deleteBullet(void)
{
	for (int i = 0; i < m_vBulletList.size(); ++i)
	{
		SAFE_DELETE(m_vBulletList[i]);
	}
}

void bulletManager::deleteBullet(int index)
{
	SAFE_DELETE(m_vBulletList[index]);
	m_vBulletList.erase(m_vBulletList.begin() + index);
}

void bulletManager::collisionCheck(void)
{
}
