#include "weaponHealkit.h"
#include "weaponManager.h"
#include "managerList.h"
#include "gDigit.h"
#include "inGame_digit.h"
#include "AnimationDef.h"
#include "characterBase.h"

using DIGIT = inGame_digit;

weaponHealkit::weaponHealkit(staticMesh::mParam param, characterBase* linkPatternDup)
: weaponBase::weaponBase(param, linkPatternDup)
{
	_infoWeapon = MN_WEAPON->getWeaponInfo(weapon_set::type::healkit);

	D3DXMATRIXA16 stRotation;
	D3DXMatrixRotationYawPitchRoll(&stRotation,
		D3DXToRadian(0.0f), D3DXToRadian(0.0f), D3DXToRadian(0.0f));
	D3DXMATRIXA16 stTranslation;
	D3DXMatrixTranslation(&stTranslation, 0.0f, 0.0f, 0.0f);

	_baseMatrix[0] = stRotation * stTranslation;
	_baseMatrix[1] = _baseMatrix[0];
}

weaponHealkit::~weaponHealkit()
{
}

void weaponHealkit::firePre(void)
{
	if (MN_KEY->mouseDown(LEFT)) _infoWeapon.autoFire = true;
	else _infoWeapon.autoFire = false;
	gDigit::pick(_infoWeapon.status, DIGIT::WEAPON::PRESS);
	if ((_bindPMesh->getAControllInfo().CurrentMotionBit & GET_ANIBITMASK(aniDefine::ANIBIT::MAIN))
		== AMAIN_HEAL)
	{
		if (MN_KEY->mouseUp())
		{
			CHANGE_BIT(_bindPMesh->getNextBit(), aniDefine::ANIBIT::MAIN, AMAIN_IDLE);
			CHANGE_BIT(_bindPMesh->getNextBit(), aniDefine::ANIBIT::SUB, AIDLE_STANDING);
			_bindPMesh->setDirectionRight(_originR);
			_bindPMesh->setDirectionUp(_originU);
			_bindPMesh->setDirectionForward(_originF);
		}
		else if(_bindPMesh->getAControllInfo().persent >= 0.8f)
		{
			//무기는 밖에서 바꿔줘야함
			_bindPMesh->getAControllInfo().persent = 0.0f;
			--_infoWeapon.current;
			CHANGE_BIT(_bindPMesh->getNextBit(), aniDefine::ANIBIT::MAIN, AMAIN_IDLE);
			CHANGE_BIT(_bindPMesh->getNextBit(), aniDefine::ANIBIT::SUB, AIDLE_STANDING); 
			_bindPMesh->setDirectionRight(_originR);
			_bindPMesh->setDirectionUp(_originU);
			_bindPMesh->setDirectionForward(_originF);
		}
	}
}

void weaponHealkit::fireDo(void)
{
	gDigit::put(_infoWeapon.status, DIGIT::WEAPON::PRESS);
	if ((_bindPMesh->getAControllInfo().NextMotionBit & GET_ANIBITMASK(aniDefine::ANIBIT::MAIN))
		!= AMAIN_HEAL)
	{
		D3DXVECTOR3 stDirection;
		_originR = _bindPMesh->getDirectRight();
		_originU = _bindPMesh->getDirectUp();
		_originF = _bindPMesh->getDirectForward();
		_bindPMesh->rotateX(-90.0f);
	}
	CHANGE_BIT(_bindPMesh->getNextBit(), aniDefine::ANIBIT::MAIN, AMAIN_HEAL);
	CHANGE_BIT(_bindPMesh->getNextBit(), aniDefine::ANIBIT::SUB, AHEAL_SELF_STANDING);
}

void weaponHealkit::firePost(void)
{
}

void weaponHealkit::reloadPre(void)
{
}

void weaponHealkit::reloadDo(void)
{
}

void weaponHealkit::reloadPost(void)
{
}
