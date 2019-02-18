#pragma once
#include "KGlobalDefine.h"
#include "pickRay.h"

class bulletBase
{
public:

	enum EBulletType
	{
		B_RIFLE,
		B_SHOTGUN,
		B_FIST,
		NONE
	};

protected:

	float _speed;

	D3DXVECTOR3 _intersect;
	pick::ray _ray;
	EBulletType _type;

public:

	//! 상태를 갱신한다
	virtual void update(void);

public:

	void setIntersect(const D3DXVECTOR3 & intersect) { _intersect = intersect; }
	void setRay(const D3DXVECTOR3 & origin, const D3DXVECTOR3 & direction);

	float & getSpeed(void) { return _speed; }
	pick::ray getRay(void) { return _ray; }
	D3DXVECTOR3 & getIntersect(void) { return _intersect; }


public:

	bulletBase(float speed, EBulletType type = EBulletType::B_RIFLE);

	virtual ~bulletBase(void);

};