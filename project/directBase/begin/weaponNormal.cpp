#include "weaponNormal.h"
#include "characterBase.h"
#include "weaponManager.h"
#include "gDigit.h"
#include "inGame_digit.h"
#include "inGame_value.h"
#include "AnimationDef.h"
#include "patternMesh.h"
#include "bulletManager.h"
#include "managerList.h"
#include "camera.h"
#include "sceneBase.h"

using DIGIT = inGame_digit;

weaponNormal::weaponNormal(characterBase * linkPatternDup, int damage)
	:weaponBase::weaponBase(linkPatternDup)
{
	_infoWeapon = MN_WEAPON->getWeaponInfo(weapon_set::type::zombie);
	_infoWeapon.damage = damage;
	_infoWeapon.shotDelay = 0.0f;

	D3DXMatrixIdentity(&_baseMatrix[0]);
	D3DXMatrixIdentity(&_baseMatrix[1]);
}

weaponNormal::~weaponNormal(void)
{
}

void weaponNormal::updateWeapon(D3DXMATRIXA16 combineMatrix[], bool isCull)
{
	_isCull = true;
	updateNormal();
}

void weaponNormal::normalPre(void)
{
	gDigit::pick(_bindPMesh->getInfoCharacter().status, DIGIT::CHAR::ATTACK);
	int currentBit = _bindPMesh->getAControllInfo().CurrentMotionBit;

	switch (_bindPMesh->getOriginMesh()->getOriginType())
	{
	case patternMesh::type::male_zombie:
	case patternMesh::type::feMale_zombie:
	{
		if ((currentBit & GET_ANIBITMASK(aniDefine::ANIBIT::MAIN)) == MALE_ATTACK)
		{
			if (_bindPMesh->getAControllInfo().persent >= 0.9f)
			{
				D3DXVECTOR3 stNeckPosition = _bindPMesh->getPosition();
				stNeckPosition.y += 9.0f;
				MN_BULLET->addBullet(stNeckPosition, GET_CAMERA()->getDirectForward(), 
					inGame_value::bullet::speed, _bindPMesh);
			}
		}
	}
		break;
	case patternMesh::type::hulk_zombie:
		break;
	}
}

void weaponNormal::normalDo(void)
{
	gDigit::put(_bindPMesh->getInfoCharacter().status, DIGIT::CHAR::ATTACK);
	switch (_bindPMesh->getOriginMesh()->getOriginType())
	{
	case patternMesh::type::male_zombie:
	case patternMesh::type::feMale_zombie:
	{
		CHANGE_BIT(_bindPMesh->getNextBit(), aniDefine::ANIBIT::MAIN, MALE_ATTACK);
		CHANGE_BIT(_bindPMesh->getNextBit(), aniDefine::ANIBIT::SUB, MALE_ATTACK_NONE);
	}
	break;
	case patternMesh::type::hulk_zombie:
		break;
	}
}

void weaponNormal::normalPost(void)
{
	_infoWeapon.nextFireTime = _infoWeapon.shotDelay + MN_TIME->getRunningTime();
}

bool weaponNormal::isNormalPossible(void)
{
	return (MN_TIME->getRunningTime() > _infoWeapon.nextFireTime) &&
		(gDigit::chk(_bindPMesh->getInfoCharacter().status, DIGIT::CHAR::ADJACENT));
			//&&!(gDigit::chk(_bindPMesh->getInfoCharacter().status, DIGIT::CHAR::DEAD))));
}
