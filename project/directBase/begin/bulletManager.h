#pragma once

#include "kGlobalDefine.h"
#include "bullet.h"

class bulletManager
{

public:

	void update(void);
	void draw(void);

public:

	void addBullet(const D3DXVECTOR3 & origin, const D3DXVECTOR3 & direction, float speed);
	void setPosition(int index, const D3DXVECTOR3 & position, bool onOff);
	void deleteBullet(void);
	void deleteBullet(int index);
	void collisionCheck(void);

public:
	
	std::vector<bullet*> & getBulletList(void) { return m_vBulletList; }

public:
	bulletManager();
	~bulletManager();

private:
	std::vector<bullet*> m_vBulletList;
};