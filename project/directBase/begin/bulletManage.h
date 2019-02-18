#pragma once

#include "kGlobalDefine.h"
#include "bulletBase.h"

#define BULLET_MAX 12

class bulletManage
{
private:

	std::vector<bulletBase*> _vBullet;

public:
	
	std::vector<bulletBase*> & getBulletList(void) { return _vBullet; }

public:

	void update(void);

public:

	void addBullet(const D3DXVECTOR3 & position, const D3DXVECTOR3 & forwardDir, float speed, 
		bulletBase::EBulletType type = bulletBase::EBulletType::B_RIFLE);

	void eraseBullet(int index);

public:
	DECLARE_SINGLETON(bulletManage);

public:
	bulletManage(void);
	virtual ~bulletManage(void);

};