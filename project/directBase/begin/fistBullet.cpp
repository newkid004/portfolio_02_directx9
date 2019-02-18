#include "fistBullet.h"

fistBullet::fistBullet(float speed, EBulletType type)
:
bulletBase(speed, type)
{
}

fistBullet::~fistBullet(void)
{
}

void fistBullet::update(void)
{

}

void fistBullet::setRange(void)
{
	_destOrigin = _ray.origin + _ray.direction * _speed;
}
