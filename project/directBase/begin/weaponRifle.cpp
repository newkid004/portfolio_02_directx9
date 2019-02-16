#include "weaponRifle.h"
#include "weaponBase.h"

weaponRifle::weaponRifle()
{
	_infoWeapon.type = weapon_set::type::rifle;
	_infoWeapon.current = 30;
	_infoWeapon.reload = 30;
	_infoWeapon.maximum = 180;

	D3DXMATRIXA16 stRotation;
	D3DXMatrixRotationYawPitchRoll(&stRotation,
		D3DXToRadian(70.0f), D3DXToRadian(205.0f), D3DXToRadian(180.0f));
	D3DXMATRIXA16 stTranslation;
	D3DXMatrixTranslation(&stTranslation, -15.0f, 3.0f, -8.0f);

	_baseMatrix[0] = stRotation * stTranslation;

	D3DXMatrixRotationYawPitchRoll(&stRotation,
		D3DXToRadian(90.0f), D3DXToRadian(175.0f), D3DXToRadian(-15.0f));
	D3DXMatrixTranslation(&stTranslation, 1.5f, 0.5f, -2.5f);

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
	//ÃÑ¾Ë ¹ß»ç
	//_bindBullet->
	--_infoWeapon.current;
}

void weaponRifle::firePost(void)
{
	weaponBase::firePost();
}

void weaponRifle::reloadPre(void)
{
	weaponBase::reloadPre();
}

void weaponRifle::reloadDo(void)
{
	weaponBase::reloadDo();
	++_infoWeapon.current;
}

void weaponRifle::reloadPost(void)
{
	weaponBase::reloadPost();
}
