#pragma once

#include "bulletBase.h"
#include "renderObject.h"
class gunBullet : public bulletBase, public renderObject
{

public:

	virtual void update(void) override;

protected:			// protected �Լ�

	//! ��ü�� �׸��� ��
	virtual void drawPre(void) override;

	//! ��ü�� �׸���
	virtual void drawDo(void) override;

	//! ��ü�� �׸� ��
	virtual void drawPost(void) override;

public:

	gunBullet(float speed, EBulletType type = EBulletType::B_RIFLE);
	virtual ~gunBullet(void);

private:

	LPD3DXMESH createBulletMesh(void);

private:

	LPD3DXMESH m_pBulletMesh;

};