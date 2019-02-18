#include "bulletBase.h"
#include "gFunc.h"

bulletBase::bulletBase(float speed, EBulletType type)
:
_speed(speed),
_type(type),
_intersect(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
	
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
