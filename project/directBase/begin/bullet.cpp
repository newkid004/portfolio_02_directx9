#include "bullet.h"
#include "managerList.h"

bullet::bullet(const D3DXVECTOR3 & origin, const D3DXVECTOR3 & direction, float speed)
	:
	m_fSpeed(speed)
{
	m_ray.origin = _position = origin;
	m_ray.direction = direction;
	m_pBulletMesh = this->createBulletMesh();

	this->setPosition(_position);
}

bullet::~bullet(void)
{
	SAFE_RELEASE(m_pBulletMesh);
}

void bullet::update(void)
{
	renderObject::update();

	m_ray.origin = _position;
}

void bullet::drawPre(void)
{
	renderObject::drawPre();
}

void bullet::drawDo(void)
{
	renderObject::drawDo();

	D3DXMATRIXA16 stWorldMatrix = this->getMatrixFinal();
	D3DXMATRIXA16 stTranslationMatrix;
	D3DXMatrixTranslation(&stTranslationMatrix, m_ray.direction.x * m_fSpeed,
		m_ray.direction.y * m_fSpeed,
		m_ray.direction.z * m_fSpeed);

	stWorldMatrix *= stTranslationMatrix;
	
	this->setPosition(D3DXVECTOR3(_position.x + m_ray.direction.x * m_fSpeed,
		_position.y + m_ray.direction.y * m_fSpeed,
		_position.z + m_ray.direction.z * m_fSpeed));


	MN_DEV->SetTransform(D3DTS_WORLD, &stWorldMatrix);

	m_pBulletMesh->DrawSubset(0);
}

void bullet::drawPost(void)
{
	renderObject::drawPost();
}

LPD3DXMESH bullet::createBulletMesh(void)
{
	LPD3DXMESH pMesh = nullptr;

	D3DXCreateCylinder(MN_DEV, 0.5, 0.5, 1, 20, 20, &pMesh, NULL);

	return pMesh;
}
