#include "weaponShotgun.h"

weaponShotgun::weaponShotgun()
{
	_infoWeapon.type = weapon_set::type::shotgun;
	_infoWeapon.current = 5;
	_infoWeapon.reload = 5;
	_infoWeapon.maximum = 30;

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
}

void weaponShotgun::fireDo(void)
{
}

void weaponShotgun::firePost(void)
{
}

void weaponShotgun::reloadPre(void)
{
}

void weaponShotgun::reloadDo(void)
{
}

void weaponShotgun::reloadPost(void)
{
}
