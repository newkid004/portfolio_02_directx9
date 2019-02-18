#include "weaponRifle.h"
#include "weaponBase.h"
#include "patternMeshDup.h"
#include "gFunc.h"

weaponRifle::weaponRifle(patternMeshDup* linkPatternDup)
	:weaponBase::weaponBase(linkPatternDup)
{
	_infoWeapon.type = weapon_set::type::rifle;
	_infoWeapon.current = 30;
	_infoWeapon.reload = 30;
	_infoWeapon.maximum = 180;
	_infoWeapon.nextFireTime = 0.2f;
	_infoWeapon.nextReloadTime = 2.0f;

	D3DXMATRIXA16 stRotation;
	D3DXMatrixRotationYawPitchRoll(&stRotation,
		D3DXToRadian(70.0f), D3DXToRadian(205.0f), D3DXToRadian(180.0f));
	D3DXMATRIXA16 stTranslation;
	D3DXMatrixTranslation(&stTranslation, -15.0f, 3.0f, -8.0f);

	_baseMatrix[0] = stRotation * stTranslation;

	D3DXMatrixRotationYawPitchRoll(&stRotation,
		D3DXToRadian(90.0f), D3DXToRadian(175.0f), D3DXToRadian(-15.0f));
	D3DXMatrixTranslation(&stTranslation, 0.0f, 0.0f, -1.0f);

	_baseMatrix[1] = stRotation * stTranslation;
}

weaponRifle::~weaponRifle()
{
}

void weaponRifle::firePre(void)
{
	weaponBase::firePre();
}

void weaponRifle::fireDo(void)
{
	weaponBase::fireDo();
	//총알 발사
	//_bindBullet->
	// 각도 _bindPMesh->getDirectForward()
	// 스피드
	//gFunc::rndInt(10, 15);
}

void weaponRifle::firePost(void)
{
	weaponBase::firePost();
	--_infoWeapon.current;
}

void weaponRifle::reloadPre(void)
{
	weaponBase::reloadPre();
}

void weaponRifle::reloadDo(void)
{
	weaponBase::reloadDo();
	if (_infoWeapon.maximum >= _infoWeapon.reload)
	{
		int need = _infoWeapon.reload - _infoWeapon.current;
		_infoWeapon.current += need;
		_infoWeapon.maximum -= need;
	}
	else
	{
		int have = _infoWeapon.reload - _infoWeapon.maximum;
		_infoWeapon.current += have;
		_infoWeapon.maximum -= have;
	}
	_isLeft = false;
}

void weaponRifle::reloadPost(void)
{
	weaponBase::reloadPost();
}
