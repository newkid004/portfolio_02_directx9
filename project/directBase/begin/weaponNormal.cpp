#include "weaponNormal.h"
#include "characterBase.h"

weaponNormal::weaponNormal(characterBase * linkPatternDup, int damage)
	:weaponBase::weaponBase(linkPatternDup)
{
	_infoWeapon.type = weapon_set::type::none;
	_infoWeapon.damage = damage;
	_infoWeapon.shotDelay = 1.0f;

	D3DXMatrixIdentity(&_baseMatrix[0]);
	D3DXMatrixIdentity(&_baseMatrix[1]);
}

weaponNormal::~weaponNormal(void)
{
}

void weaponNormal::firePre(void)
{
	weaponBase::firePre();
}

void weaponNormal::fireDo(void)
{
	weaponBase::fireDo();
	D3DXVECTOR3 stPosition = _position;
	D3DXVec3TransformCoord(&stPosition, &stPosition, &_bindPMesh->getFinalNeckMatrix());
	//_bulletManager.addBullet(stPosition, _bindPMesh->getDirectForward())
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
