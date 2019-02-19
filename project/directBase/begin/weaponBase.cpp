#include "weaponBase.h"

#include "managerList.h"
#include "gDigit.h"

#include "inGame_digit.h"

#include "bulletManager.h"
#include "characterBase.h"
#include "AnimationDef.h"

using DIGIT = inGame_digit;

weaponBase::weaponBase(staticMesh::mParam param , characterBase* linkPatternDup)
	:staticMesh::staticMesh(param),_bindPMesh(linkPatternDup)
{
}

weaponBase::weaponBase(characterBase * linkPatternDup)
	:_bindPMesh(linkPatternDup)
{
}

weaponBase::~weaponBase()
{
}

void weaponBase::updateWeapon(D3DXMATRIXA16 combineMatrix[], bool isCull)
{
	_isLeft = (gDigit::chk(_infoWeapon.status, DIGIT::WEAPON::RELOAD) ? false : true);
	updateFire();
	updateReload();
	
	updateHandMatrix(combineMatrix);
	staticMesh::update();
	_isCull = isCull;
	(*getMatrixWorldPoint()) = (*getMatrixWorldPoint()) * _localMatrix;

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
	int &nextBit = _bindPMesh->getNextBit();
	if ((nextBit & GET_ANIBITMASK(aniDefine::ANIBIT::MIX)) == AMIX_RELOAD)
	{
		if (_bindPMesh->getAControllInfo().persent >= 0.8f)
		{
			reloadBullet();
			if (_infoWeapon.current >= _infoWeapon.reload || _infoWeapon.maximum == 0)
			{
				CHANGE_BIT(nextBit, aniDefine::ANIBIT::MIX, AMIX_NONE);
			}
		}
	}

}

void weaponBase::reloadDo(void)
{
	gDigit::put(_infoWeapon.status, DIGIT::WEAPON::RELOAD);
	CHANGE_BIT(_bindPMesh->getNextBit(), aniDefine::ANIBIT::MIX, AMIX_RELOAD);
}

void weaponBase::reloadPost(void)
{
	_infoWeapon.nextReloadTime = _infoWeapon.reloadDelay + MN_TIME->getRunningTime();
}

void weaponBase::updateHandMatrix(D3DXMATRIXA16 combineMatrix[])
{
	_localMatrix = _baseMatrix[0] * combineMatrix[0];
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
