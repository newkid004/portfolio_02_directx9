#pragma once

#include "kGlobalDefine.h"
#include "gunBullet.h"
#include "fistBullet.h"

#define BULLET_MAX 12

class bulletManager
{
private:

	std::vector<gunBullet*> _vGunBulletList;
	std::vector<fistBullet*> _vFistBulletList;

public:
	
	std::vector<gunBullet*> & getGunBulletList(void) { return _vGunBulletList; }
	std::vector<fistBullet*> & getFistBulletList(void) { return _vFistBulletList; }

public:

	void update(void);
	void draw(void);

public:

	void addBullet(const D3DXVECTOR3 & position, const D3DXVECTOR3 & forwardDir, float speed, 
		bulletBase::EBulletType type = bulletBase::EBulletType::B_RIFLE);

	void eraseGunBullet(int index);
	void eraseFistBullet(int index);

public:
	DECLARE_SINGLETON(bulletManager);

public:
	bulletManager(void);
	virtual ~bulletManager(void);

};