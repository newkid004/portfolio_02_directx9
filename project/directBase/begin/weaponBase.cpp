#include "weaponBase.h"

#include "managerList.h"
#include "gDigit.h"

#include "inGame_digit.h"
#include "inGame_value.h"

#include "bulletManager.h"
#include "characterBase.h"
#include "AnimationDef.h"
#include "sceneBase.h"
#include "camera.h"

#include "eShootWeapon.h"

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
	updateNormal();
	
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
	else if(_infoWeapon.type != weapon_set::type::healkit &&
		MN_KEY->mousePress())
	{
		MN_SND->find("emptyClip")->play();
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

void weaponBase::updateNormal(void)
{
	normalPre();
	if (isNormalPossible())
	{
		normalDo();
		normalPost();
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

	// ----- event ----- //
	MN_EVENT->add(new eventBase(_bindPMesh, nullptr,
		EVENT::TYPE::WEAPON |
		EVENT::ACT::WEAPON::SHOOT));
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
				if (_infoWeapon.type == weapon_set::type::rifle)
				{
					MN_SND->find("rReady")->play();
				}
			}
		}
	}
}

void weaponBase::reloadDo(void)
{
	gDigit::put(_infoWeapon.status, DIGIT::WEAPON::RELOAD);
	CHANGE_BIT(_bindPMesh->getNextBit(), aniDefine::ANIBIT::MIX, AMIX_RELOAD);
	if (_infoWeapon.type == weapon_set::type::rifle)
	{
		MN_SND->find("rClipOut")->play();
	}
}

void weaponBase::reloadPost(void)
{
	_infoWeapon.nextReloadTime = _infoWeapon.reloadDelay + MN_TIME->getRunningTime();
}

void weaponBase::normalPre(void)
{
	gDigit::pick(_infoWeapon.status, DIGIT::WEAPON::ATTACK);
	if ((_bindPMesh->getAControllInfo().CurrentMotionBit & GET_ANIBITMASK(aniDefine::ANIBIT::MIX))
		== AMIX_ATTACK)
	{
		if (_bindPMesh->getAControllInfo().persent >= 0.7f)
		//if(_bindPMesh->getAControllInfo().isEnd)
		{
			CHANGE_BIT(_bindPMesh->getNextBit(), aniDefine::ANIBIT::MIX, AMIX_NONE);
		}
	}
}

void weaponBase::normalDo(void)
{
	gDigit::put(_infoWeapon.status, DIGIT::WEAPON::ATTACK);
	CHANGE_BIT(_bindPMesh->getNextBit(), aniDefine::ANIBIT::MIX, AMIX_ATTACK);
	//D3DXVECTOR3 stNeckPosition = _position;
	//D3DXVec3TransformCoord(&stNeckPosition, &stNeckPosition, &_bindPMesh->getFinalNeckMatrix());

	// 공격 타입 보존
	int preType = _infoWeapon.type;
	_infoWeapon.type = weapon_set::type::none;

	MN_BULLET->addBullet(GET_CAMERA()->getPosition(), GET_CAMERA()->getDirectForward(),
		10.0f, this);
	MN_SND->find("swingWeapon")->play();

	_infoWeapon.type = preType;
}

void weaponBase::normalPost(void)
{
	_infoWeapon.nextFireTime = MN_WEAPON->getWeaponInfo(weapon_set::type::none).shotDelay + MN_TIME->getRunningTime();
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

bool weaponBase::isNormalPossible(void)
{
	return(MN_TIME->getRunningTime() > _infoWeapon.nextFireTime) &&	(MN_KEY->mousePress(EMouseInput::RIGHT));
}

bool weaponBase::needReload(void)
{
	return !gDigit::chk(_infoWeapon.status, DIGIT::WEAPON::PRESS) && _infoWeapon.current < _infoWeapon.reload;
}
