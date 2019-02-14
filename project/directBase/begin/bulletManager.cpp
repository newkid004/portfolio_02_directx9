#include "bulletManager.h"
#include "gFunc.h"

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

		if (gFunc::Vec3Distance(m_vBulletList[i]->getPickRay().origin, m_vBulletList[i]->getPosition()) > 80)
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
