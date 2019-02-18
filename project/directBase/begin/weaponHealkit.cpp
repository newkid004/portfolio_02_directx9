#include "weaponHealkit.h"

weaponHealkit::weaponHealkit(staticMesh::mParam param, characterBase* linkPatternDup)
: weaponBase::weaponBase(param, linkPatternDup)
{
	_infoWeapon.type = weapon_set::type::healkit;
	_infoWeapon.current = 1;
	_infoWeapon.reload = 1;
	_infoWeapon.maximum = 0;

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
	weaponBase::firePre();
}

void weaponHealkit::fireDo(void)
{
	weaponBase::fireDo();
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
