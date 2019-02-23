#pragma once

#include "bulletBase.h"
#include "renderObject.h"

class weaponBase;

class gunBullet : public bulletBase, public renderObject
{

public:

	virtual void update(void) override;

protected:			// protected 함수

	//! 물체를 그리기 전
	virtual void drawPre(void) override;

	//! 물체를 그린다
	virtual void drawDo(void) override;

	//! 물체를 그린 후
	virtual void drawPost(void) override;

public:

	gunBullet(float speed, weaponBase * bind);
	virtual ~gunBullet(void);

public:

	pick::ray & getRay(void) { return _ray; }
private:

	LPD3DXMESH createBulletMesh(void);

private:

	LPD3DXMESH m_pBulletMesh;

};