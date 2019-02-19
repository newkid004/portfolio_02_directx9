#include "weaponShotgun.h"
#include "gDigit.h"
#include "inGame_digit.h"
#include "weaponManager.h"

weaponShotgun::weaponShotgun(staticMesh::mParam param , characterBase* linkPatternDup, int damage)
	:weaponBase::weaponBase(param, linkPatternDup)
{
	_infoWeapon = MN_WEAPON->getWeaponInfo(weaponManager::weaponType::shotgun);
	_infoWeapon.damage = damage;

	D3DXMATRIXA16 stRotation;
	D3DXMatrixRotationYawPitchRoll(&stRotation,
		D3DXToRadian(60.0f), D3DXToRadian(195.0f), D3DXToRadian(160.0f));
	D3DXMATRIXA16 stTranslation;
	D3DXMatrixTranslation(&stTranslation, -19.0f, 3.0f, -14.0f);

	_baseMatrix[0] = stRotation * stTranslation;

	D3DXMatrixRotationYawPitchRoll(&stRotation,
		D3DXToRadian(70.0f), D3DXToRadian(190.0f), D3DXToRadian(-10.0f));
	D3DXMatrixTranslation(&stTranslation, 1.5f, 0.5f, -2.5f);

	_baseMatrix[1] = stRotation * stTranslation;
}


weaponShotgun::~weaponShotgun()
{
}

void weaponShotgun::firePre(void)
{
	weaponBase::firePre();
}

void weaponShotgun::fireDo(void)
{
	weaponBase::fireDo();
	GET_BULLET_MANAGER()->addBullet(_handPosition, _targetDirection,
		1.0f, bulletBase::EBulletType::B_SHOTGUN);
}

void weaponShotgun::firePost(void)
{
	weaponBase::firePost();
	--_infoWeapon.current;
}

void weaponShotgun::reloadPre(void)
{
	weaponBase::reloadPre();
}

void weaponShotgun::reloadDo(void)
{
	weaponBase::reloadDo();
}

void weaponShotgun::reloadPost(void)
{
	weaponBase::reloadPost();
}

void weaponShotgun::reloadBullet()
{
	++_infoWeapon.current;
	--_infoWeapon.maximum;
}

void weaponShotgun::updateHandMatrix(D3DXMATRIXA16 combineMatrix[])
{
	if (_isLeft)
	{
		_localMatrix = _baseMatrix[0] * combineMatrix[0];
	}
	else
	{
		_localMatrix = _baseMatrix[1] * combineMatrix[1];
	}
}
