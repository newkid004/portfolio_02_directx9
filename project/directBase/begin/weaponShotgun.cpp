#include "weaponShotgun.h"
#include "gDigit.h"

#include "inGame_digit.h"
#include "inGame_value.h"

#include "weaponManager.h"
#include "soundManager.h"
#include "gFunc.h"
#include "managerList.h"
#include "camera.h"
#include "sceneBase.h"

weaponShotgun::weaponShotgun(staticMesh::mParam param , characterBase* linkPatternDup, int damage)
	:weaponBase::weaponBase(param, linkPatternDup)
{
	this->setScale(0.03f);
	_infoWeapon = MN_WEAPON->getWeaponInfo(weapon_set::type::shotgun);
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
	MN_SND->find("shotgunShoot")->play(-1.0f,gFunc::rndFloat( 0.8f, 1.0f));
}

void weaponShotgun::firePost(void)
{
	weaponBase::firePost();
	--_infoWeapon.current;
}

void weaponShotgun::reloadBullet()
{
	++_infoWeapon.current;
	--_infoWeapon.maximum; 
	MN_SND->find("sLoadShell")->play(-1.0f);
	if (_infoWeapon.current == _infoWeapon.reload)
	{
		MN_SND->find("sPump")->play();
	}
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
