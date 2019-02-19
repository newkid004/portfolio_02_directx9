#include "weaponNormal.h"
#include "characterBase.h"
#include "weaponManager.h"
#include "gDigit.h"
#include "inGame_digit.h"
#include "AnimationDef.h"

using DIGIT = inGame_digit;

weaponNormal::weaponNormal(characterBase * linkPatternDup, int damage)
	:weaponBase::weaponBase(linkPatternDup)
{
	_infoWeapon = MN_WEAPON->getWeaponInfo(weaponManager::weaponType::normal);
	_infoWeapon.damage = damage;

	D3DXMatrixIdentity(&_baseMatrix[0]);
	D3DXMatrixIdentity(&_baseMatrix[1]);
}

weaponNormal::~weaponNormal(void)
{
}

void weaponNormal::firePre(void)
{
	gDigit::pick(_infoWeapon.status, DIGIT::WEAPON::PRESS);
	if ((_bindPMesh->getAControllInfo().CurrentMotionBit &
		GET_ANIBITMASK(aniDefine::ANIBIT::TYPE)) == ATYPE_ZOMBIE_MALE)
	{
		if ((_bindPMesh->getAControllInfo().CurrentMotionBit &
			GET_ANIBITMASK(aniDefine::ANIBIT::MAIN)) == MALE_ATTACK)
		{
		}
	}
	else if ((_bindPMesh->getAControllInfo().CurrentMotionBit &
		GET_ANIBITMASK(aniDefine::ANIBIT::TYPE)) == ATYPE_ZOMBIE_FEMALE)
	{
		if ((_bindPMesh->getAControllInfo().CurrentMotionBit &
			GET_ANIBITMASK(aniDefine::ANIBIT::MAIN)) == FEMALE_ATTACK)
		{
		}
	}
	else if ((_bindPMesh->getAControllInfo().CurrentMotionBit &
		GET_ANIBITMASK(aniDefine::ANIBIT::TYPE)) == ATYPE_ZOMBIE_HULK)
	{
		if ((_bindPMesh->getAControllInfo().CurrentMotionBit &
			GET_ANIBITMASK(aniDefine::ANIBIT::MAIN)) == HULK_ATTACK)
		{
		}
	}
}

void weaponNormal::fireDo(void)
{
	//동작에 걸어줄 조건이 필요 !
	//weaponBase::fireDo();
	GET_BULLET_MANAGER()->addBullet(_handPosition, _targetDirection,
		1.0f, bulletBase::EBulletType::B_FIST);
}

void weaponNormal::firePost(void)
{
	weaponBase::firePost();
}

void weaponNormal::reloadPre(void)
{
}

void weaponNormal::reloadDo(void)
{
}

void weaponNormal::reloadPost(void)
{
}
