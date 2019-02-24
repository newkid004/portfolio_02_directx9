#include "gunBullet.h"
#include "managerList.h"

#include "characterBase.h"

gunBullet::gunBullet(float speed, weaponBase* bind)
:
bulletBase(speed, bind)
{
	m_pBulletMesh = this->createBulletMesh();
}

gunBullet::~gunBullet(void)
{
}

void gunBullet::update(void)
{
	renderObject::update();

	_ray.origin += _ray.direction * _speed;
	this->setPosition(_ray.origin);
}

void gunBullet::drawPre(void)
{
	renderObject::drawPre();
}

void gunBullet::drawDo(void)
{
	renderObject::drawDo();
	
	D3DXMATRIXA16 stWorldMatrix = this->getMatrixFinal();

	MN_DEV->SetTransform(D3DTS_WORLD, &stWorldMatrix);

	m_pBulletMesh->DrawSubset(0);
}

void gunBullet::drawPost(void)
{
	renderObject::drawPost();
}

LPD3DXMESH gunBullet::createBulletMesh(void)
{
	LPD3DXMESH pMesh = nullptr;

	D3DXCreateSphere(MN_DEV, 0.1, 20, 20, &pMesh, NULL);

	return pMesh;
}