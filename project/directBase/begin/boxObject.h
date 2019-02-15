#pragma once
#include "KGlobalDefine.h"
#include "renderObject.h"

class boxObject : public renderObject
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

	boxObject(void);

	virtual ~boxObject(void);

public:

	LPD3DXMESH & getMesh(void) { return m_pWallMesh; }
private:

	//! 벽 메쉬를 생성한다
	LPD3DXMESH createWallMesh(void);

private:

	LPD3DXMESH m_pWallMesh = nullptr;
};