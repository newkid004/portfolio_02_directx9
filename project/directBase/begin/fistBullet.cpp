#include "fistBullet.h"
#include "timeManager.h"

#include "characterBase.h"

fistBullet::fistBullet(float speed, characterBase* bind)
:
bulletBase(speed, bind)
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
