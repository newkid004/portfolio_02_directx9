#include "weaponBase.h"

#include "managerList.h"
#include "gDigit.h"

#include "inGame_digit.h"

#include "bulletManager.h"
#include "characterBase.h"
#include "AnimationDef.h"
#include "sceneBase.h"
#include "camera.h"

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

		if (gDigit::chk(_infoWeapon.status, DIGIT::WEAPON::DO_FIRE))
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
	gDigit::pick(_infoWeapon.status, DIGIT::WEAPON::PRESS);
	if ((_bindPMesh->getAControllInfo().CurrentMotionBit & GET_ANIBITMASK(aniDefine::ANIBIT::MIX)) == AMIX_SHOOT)
	{
		if (!gDigit::chk(_infoWeapon.status, DIGIT::WEAPON::DO_FIRE))
		{
			CHANGE_BIT(_bindPMesh->getNextBit(), aniDefine::ANIBIT::MIX, AMIX_NONE);
		}
		else if ((_infoWeapon.current <= 0) && gDigit::chk(_infoWeapon.status, DIGIT::WEAPON::DO_FIRE))
		{
			CHANGE_BIT(_bindPMesh->getNextBit(), aniDefine::ANIBIT::MIX, AMIX_NONE);
		}
	}
}

void weaponBase::fireDo(void)
{
	gDigit::put(_infoWeapon.status, DIGIT::WEAPON::PRESS);
	CHANGE_BIT(_bindPMesh->getNextBit(), aniDefine::ANIBIT::MIX, AMIX_SHOOT);
	_bindPMesh->getAControllInfo().trackPositionA = 0.0f;

	_handPosition = _position;
	D3DXVec3TransformCoord(&_handPosition, &_handPosition, &_bindPMesh->getLeftHandMatrix());
	if (_pickPosition == D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	{
		D3DXVECTOR3 neckPosition = _position;
		D3DXVec3TransformCoord(&neckPosition, &neckPosition, &_bindPMesh->getFinalNeckMatrix());

		//_pickPosition = neckPosition + GET_CAMERA()->getDirectForward() *100.0f;
		_pickPosition = neckPosition + _bindPMesh->getDirectForward() *100.0f;
	}

	_targetDirection = _pickPosition - _handPosition;
	D3DXVec3Normalize(&_targetDirection, &_targetDirection);

	_pickPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void weaponBase::firePost(void)
{
	_infoWeapon.nextFireTime = _infoWeapon.shotDelay + MN_TIME->getRunningTime();
}

void weaponBase::reloadPre(void)
{
	int Bit = _bindPMesh->getAControllInfo().CurrentMotionBit;
	if ((Bit & GET_ANIBITMASK(aniDefine::ANIBIT::MIX)) == AMIX_RELOAD)
	{
		if (_bindPMesh->getAControllInfo().persent >= 0.9f)
		{
			reloadBullet();
			_bindPMesh->getAControllInfo().trackPositionA = 0.0f;
			_bindPMesh->getAControllInfo().persent = 0.0f;
			if ((_infoWeapon.current >= _infoWeapon.reload) || _infoWeapon.maximum == 0)
			{
				CHANGE_BIT(_bindPMesh->getNextBit(), aniDefine::ANIBIT::MIX, AMIX_NONE);
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
	return (0 < _infoWeapon.current) && (_infoWeapon.nextFireTime < MN_TIME->getRunningTime());
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
