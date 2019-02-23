#pragma once

#include "kGlobalDefine.h"
#include "gunBullet.h"
#include "fistBullet.h"

#define BULLET_MAX 12
class player;

class weaponBase;

class bulletManager
{
private:

	std::list<gunBullet*> _vGunBulletList;
	std::list<fistBullet*> _vFistBulletList;
	std::unordered_map<std::string, int> _oPartList;

	std::list<gunBullet *>::iterator _gunIter;
	std::list<fistBullet *>::iterator _fistIter;

	player * _bindPlayer;

public:
	
	std::list<gunBullet*> & getGunBulletList(void) { return _vGunBulletList; }
	std::list<fistBullet*> & getFistBulletList(void) { return _vFistBulletList; }

	void setBindPlayer(player * bind) { _bindPlayer = bind; }
public:
	void init(void);
	void update(void);
	void draw(void);
public:

	void addBullet(const D3DXVECTOR3 & position, const D3DXVECTOR3 & forwardDir, float speed, 
		weaponBase* bind, bulletBase::TYPE type = bulletBase::TYPE::UNVISIBLE);

	bool gunCollision(gunBullet* bullet);
	bool fistCollision(fistBullet* bullet);

public:
	DECLARE_SINGLETON(bulletManager);

public:
	bulletManager(void);
	virtual ~bulletManager(void);

};