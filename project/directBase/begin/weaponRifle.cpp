#include "weaponRifle.h"
#include "weaponBase.h"
#include "characterBase.h"
#include "gFunc.h"
#include "managerList.h"

//
#include "bulletManager.h"
//

weaponRifle::weaponRifle(staticMesh::mParam param , characterBase* linkPatternDup, int damage)
	:weaponBase::weaponBase(param, linkPatternDup)
{
	_infoWeapon.type = weapon_set::type::rifle;
	_infoWeapon.current = 30;
	_infoWeapon.reload = 30;
	_infoWeapon.maximum = 180;
	_infoWeapon.damage = damage;
	_infoWeapon.shotDelay = 0.1f;
	_infoWeapon.reloadDelay = 2.0f;

	/*¿Þ¼Õ
	D3DXMatrixRotationYawPitchRoll(&stRotation,
		D3DXToRadian(70.0f), D3DXToRadian(205.0f), D3DXToRadian(180.0f));
	D3DXMatrixTranslation(&stTranslation, -15.0f, 3.0f, -8.0f);
	*/
	D3DXMATRIXA16 stRotation;
	D3DXMATRIXA16 stTranslation;

	D3DXMatrixRotationYawPitchRoll(&stRotation,
		D3DXToRadian(90.0f), D3DXToRadian(175.0f), D3DXToRadian(-15.0f));
	D3DXMatrixTranslation(&stTranslation, 0.0f, 0.0f, -1.0f);

	_baseMatrix[0] = _baseMatrix[1] = stRotation * stTranslation;
}

weaponRifle::~weaponRifle()
{
}

void weaponRifle::firePre(void)
{
	weaponBase::firePre();
	if (MN_KEY->mouseDown(LEFT)) _infoWeapon.autoFire = true;
	else _infoWeapon.autoFire = false;
}

void weaponRifle::fireDo(void)
{
	weaponBase::fireDo();
	D3DXVECTOR3 stPosition = _position;
	D3DXVec3TransformCoord(&stPosition, &stPosition, &_bindPMesh->getFinalNeckMatrix());
	//_bulletManager.addBullet(stPosition, _bindPMesh->getDirectForward(), 0.5f);
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
		_infoWeapon.current += _infoWeapon.maximum;
		_infoWeapon.maximum = 0;
	}
}

void weaponRifle::reloadPost(void)
{
	weaponBase::reloadPost();
}

void weaponRifle::updateHandMatrix(D3DXMATRIXA16 combineMatrix[])
{
	_localMatrix = _baseMatrix[1] * combineMatrix[1];
}
