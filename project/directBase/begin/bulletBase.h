#pragma once
#include "KGlobalDefine.h"
#include "pickRay.h"

class weaponBase;
class characterBase;

class bulletBase
{
public:

	enum TYPE
	{
		VISIBLE = 0,
		UNVISIBLE = 1
	};
	
protected:

	int _damage;
	int _weaponType;
	int _bulletType;

	float _speed;
	
	D3DXVECTOR3 _shootOrigin;
	D3DXVECTOR3 _intersect;
	pick::ray _ray;

public:

	//! 상태를 갱신한다
	virtual void update(void);

public:

	void setIntersect(const D3DXVECTOR3 & intersect) { _intersect = intersect; }
	void setRay(const D3DXVECTOR3 & origin, const D3DXVECTOR3 & direction);
	void setBulletType(int type) { _bulletType = type; }

	int getDamage(void) { return _damage; }
	int getWeaponType(void) { return _weaponType; }
	int getBulletType(void) { return _bulletType; }
	float & getSpeed(void) { return _speed; }
	pick::ray & getRay(void) { return _ray; }
	D3DXVECTOR3 & getIntersect(void) { return _intersect; }

public:

	bulletBase(float speed, weaponBase* bind);

	virtual ~bulletBase(void);

};