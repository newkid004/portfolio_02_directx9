#include "fistBullet.h"
#include "timeManager.h"

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
	_fPlayTime -= GET_TIME_MANAGER()->getDeltaTime();
}

void fistBullet::setRange(void)
{
	_destOrigin = _ray.origin + _ray.direction * _speed;
}
