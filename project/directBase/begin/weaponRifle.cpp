#include "weaponRifle.h"

#include "managerList.h"
#include "gFunc.h"

#include "inGame_value.h"

#include "characterBase.h"
#include "bulletBase.h"
#include "camera.h"
#include "sceneBase.h"
#include "soundManager.h"

weaponRifle::weaponRifle(staticMesh::mParam param , characterBase* linkPatternDup, int damage)
	:weaponBase::weaponBase(param, linkPatternDup)
{
	this->setScale(0.03f);
	_infoWeapon = MN_WEAPON->getWeaponInfo(weapon_set::type::rifle);
	_infoWeapon.damage = damage;

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
	/*
	¿À·ù³ª¼­ ÁÖ¼®ÃÆ½À´Ï´Ù <¹ÚÀçÈ«>
	¤·¤»
	*/
	auto stRay = gFunc::createPickRay(MN_KEY->getMousePos(), GET_CAMERA()->getPosition());
	GET_BULLET_MANAGER()->addBullet(stRay.origin, stRay.direction,
		inGame_value::bullet::speed, this);
	GET_BULLET_MANAGER()->addBullet(_handPosition, _targetDirection,
		inGame_value::bullet::speed, this, bulletBase::TYPE::VISIBLE);
	MN_SND->find("rifleShoot")->play(-1.0f, gFunc::rndFloat(0.5f,1.0f));
}

void weaponRifle::firePost(void)
{
	weaponBase::firePost();
	--_infoWeapon.current;
}

void weaponRifle::reloadBullet()
{
	if (_infoWeapon.current + _infoWeapon.maximum >= _infoWeapon.reload)
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
	MN_SND->find("rClipIn")->play();
}

void weaponRifle::updateHandMatrix(D3DXMATRIXA16 combineMatrix[])
{
	_localMatrix = _baseMatrix[1] * combineMatrix[1];
}
