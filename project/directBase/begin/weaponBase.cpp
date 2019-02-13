#include "weaponBase.h"

#include "managerList.h"

weaponBase::weaponBase()
{
	D3DXMatrixIdentity(&_baseMatrix);
}

weaponBase::~weaponBase()
{
}

void weaponBase::update(void)
{
	updateFire();
	updateReload();
}

void weaponBase::updateFire(void)
{
	firePre();

	if (isShotPossible())
	{
		if (!_infoWeapon.autoFire)
		{
			if (_isPressed)
				return;
		}

		if (MN_KEY->mouseDown())
		{
			_isReloading = false;

			fireDo();
			firePost();
		}
	}
}

void weaponBase::updateReload(void)
{
	reloadPre();

	if (isReloadPossible())
	{
		if (MN_KEY->keyPress(DIK_R) && !isStillFire())
		{
			reloadDo();
			reloadPost();
		}
	}
}

void weaponBase::firePre(void)
{
	if (MN_KEY->mouseUp())
		_isPressed = false;
}

void weaponBase::fireDo(void)
{
	_isPressed = true;
}

void weaponBase::firePost(void)
{
	_nextFireTime = _infoWeapon.shotDelay + MN_TIME->getRunningTime();
}

void weaponBase::reloadPre(void)
{
}

void weaponBase::reloadDo(void)
{
	_isReloading = true;
}

void weaponBase::reloadPost(void)
{
	_nextReloadTime = _infoWeapon.reloadDelay + MN_TIME->getRunningTime();
}

bool weaponBase::isShotPossible(void)
{
	return 0 < _infoWeapon.current && (_nextFireTime < MN_TIME->getRunningTime());
}

bool weaponBase::isReloadPossible(void)
{
	return _infoWeapon.current < _infoWeapon.reload && 0 < _infoWeapon.maximum && (_nextFireTime < MN_TIME->getRunningTime());
}

bool weaponBase::isStillFire(void)
{
	return _isPressed || (MN_TIME->getRunningTime() < _nextFireTime);
}

bool weaponBase::needReload(void)
{
	return !_isPressed && _infoWeapon.current < _infoWeapon.reload;
}
