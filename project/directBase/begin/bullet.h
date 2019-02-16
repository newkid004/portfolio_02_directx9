#pragma once
#include "KGlobalDefine.h"
#include "renderObject.h"
#include "pickRay.h"

class bullet : public renderObject
{
public:

	//! 상태를 갱신한다
	virtual void update(void) override;

protected:			// protected 함수

	//! 물체를 그리기 전
	virtual void drawPre(void) override;

	//! 물체를 그린다
	virtual void drawDo(void) override;

	//! 물체를 그린 후
	virtual void drawPost(void) override;

public:

	bullet(const D3DXVECTOR3 & origin, const D3DXVECTOR3 & direction, float speed);

	virtual ~bullet(void);

public:
	void setOnOff(bool onOff) { m_onOff = onOff; }
	void setIntersect(const D3DXVECTOR3 & intersect) { m_stIntersect = intersect; }
	float getSpeed(void) { return m_fSpeed; }
	D3DXVECTOR3 & getPosition(void) { return _position; }
	LPD3DXMESH getBulletMesh(void) { return m_pBulletMesh; }
	pick::ray & getPickRay(void) { return m_ray; }

private:

	//! 벽 메쉬를 생성한다
	LPD3DXMESH createBulletMesh(void);

private:
	bool m_onOff = true;
	float m_fSpeed = 0.0f;
	LPD3DXMESH m_pBulletMesh = nullptr;
	D3DXVECTOR3 m_stIntersect;

	pick::ray m_ray;
};