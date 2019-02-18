#include "weaponBase.h"

#include "managerList.h"
#include "gDigit.h"

#include "inGame_digit.h"

using DIGIT = inGame_digit;

weaponBase::weaponBase(patternMeshDup* linkPatternDup)
	:_bindPMesh(linkPatternDup)
{
}

weaponBase::~weaponBase()
{
}

void weaponBase::updateWeapon(D3DXMATRIXA16 combineMatrix[], bool isCull)
{
	D3DXMATRIXA16 stLocalMatrix;
	if (_isLeft)
	{
		stLocalMatrix = _baseMatrix[0] * combineMatrix[0];
	}
	else
	{
		stLocalMatrix = _baseMatrix[1] * combineMatrix[1];
	}
	staticMesh::update();
	_isCull = isCull;
	(*getMatrixWorldPoint()) = (*getMatrixWorldPoint()) * stLocalMatrix;
	updateFire();
	updateReload();

	/*

	왼손 오른손 적용 문제 해결 필요
	*/
}

void weaponBase::updateFire(void)
{
	firePre();

	if (isShotPossible())
	{
		if (!_infoWeapon.autoFire)
		{
			if (gDigit::chk(_infoWeapon.status, DIGIT::WEAPON::PRESS))
				return;
		}

		if (MN_KEY->mouseDown())
		{
			gDigit::pick(_infoWeapon.status, DIGIT::WEAPON::RELOAD);

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
		gDigit::pick(_infoWeapon.status, DIGIT::WEAPON::PRESS);
}

void weaponBase::fireDo(void)
{
	gDigit::put(_infoWeapon.status, DIGIT::WEAPON::PRESS);
}

void weaponBase::firePost(void)
{
	_infoWeapon.nextFireTime = _infoWeapon.shotDelay + MN_TIME->getRunningTime();
}

void weaponBase::reloadPre(void)
{
}

void weaponBase::reloadDo(void)
{
	gDigit::put(_infoWeapon.status, DIGIT::WEAPON::RELOAD);
}

void weaponBase::reloadPost(void)
{
	_infoWeapon.nextReloadTime = _infoWeapon.reloadDelay + MN_TIME->getRunningTime();
}

bool weaponBase::isShotPossible(void)
{
	return 0 < _infoWeapon.current && (_infoWeapon.nextFireTime < MN_TIME->getRunningTime());
}

bool weaponBase::isReloadPossible(void)
{
	return _infoWeapon.current < _infoWeapon.reload && 0 < _infoWeapon.maximum && (_infoWeapon.nextFireTime < MN_TIME->getRunningTime());
}

bool weaponBase::isStillFire(void)
{
	return gDigit::chk(_infoWeapon.status, DIGIT::WEAPON::PRESS) || (MN_TIME->getRunningTime() < _infoWeapon.nextFireTime);
}

bool weaponBase::needReload(void)
{
	return !gDigit::chk(_infoWeapon.status, DIGIT::WEAPON::PRESS) && _infoWeapon.current < _infoWeapon.reload;
}
