#pragma once
#include "KGlobalDefine.h"
#include "pickRay.h"

class characterBase;

class bulletBase
{
public:

	//enum EBulletType
	//{
	//	// ----- survivor ----- //
	//	B_RIFLE,
	//	B_SHOTGUN,
	//	B_FIST,

	//	// ----- enemy ---- //
	//	B_ZOMBIE,
	//	B_TANK,

	//	NONE
	//};

protected:

	characterBase* _bindCharacter = nullptr;

	float _speed;

	D3DXVECTOR3 _shootOrigin;
	D3DXVECTOR3 _intersect;
	pick::ray _ray;

	// EBulletType _type;

public:

	//! 상태를 갱신한다
	virtual void update(void);

public:

	void setIntersect(const D3DXVECTOR3 & intersect) { _intersect = intersect; }
	void setRay(const D3DXVECTOR3 & origin, const D3DXVECTOR3 & direction);

	float & getSpeed(void) { return _speed; }
	pick::ray & getRay(void) { return _ray; }
	D3DXVECTOR3 & getIntersect(void) { return _intersect; }

	characterBase* & refBindCharacter(void) { return _bindCharacter; }

public:

	bulletBase(float speed, characterBase* bind);

	virtual ~bulletBase(void);

};