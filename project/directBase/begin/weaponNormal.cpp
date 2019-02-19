#include "weaponNormal.h"
#include "characterBase.h"
#include "weaponManager.h"

weaponNormal::weaponNormal(characterBase * linkPatternDup, int damage)
	:weaponBase::weaponBase(linkPatternDup)
{
	_infoWeapon = MN_WEAPON->getWeaponInfo(weaponManager::Type::normal);
	_infoWeapon.damage = damage;

	D3DXMatrixIdentity(&_baseMatrix[0]);
	D3DXMatrixIdentity(&_baseMatrix[1]);
}

weaponNormal::~weaponNormal(void)
{
}

void weaponNormal::firePre(void)
{
}

void weaponNormal::fireDo(void)
{
	//동작에 걸어줄 조건이 필요 !

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
