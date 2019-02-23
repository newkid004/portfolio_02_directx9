#include "eHitBullet.h"

#include "bulletBase.h"
#include "characterBase.h"

eHitBullet::eHitBullet(void * bullet, void * take, unsigned long param) :
	eventBase(bullet, take, param)
{
	auto viewBullet = static_cast<bulletBase*>(bullet);
	auto viewTake = static_cast<characterBase*>(take);
}