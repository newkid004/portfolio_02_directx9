#include "bulletBase.h"
#include "gFunc.h"

#include "characterBase.h"

bulletBase::bulletBase(float speed, weaponBase* bind)
:
_speed(speed),
_intersect(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
	_damage = bind->getInfoWeapon().damage;
	_weaponType = bind->getInfoWeapon().type;
}

bulletBase::~bulletBase(void)
{
}

void bulletBase::update(void)
{
	
}

void bulletBase::setRay(const D3DXVECTOR3 & origin, const D3DXVECTOR3 & direction)
{
	_ray.origin = origin;
	_ray.direction = direction;
	_shootOrigin = origin;
}
