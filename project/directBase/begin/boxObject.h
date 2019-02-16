#pragma once
#include "KGlobalDefine.h"
#include "renderObject.h"

class boxObject : public renderObject
{
public:

	//! ���¸� �����Ѵ�
	virtual void update(void) override;

protected:			// protected �Լ�

	//! ��ü�� �׸��� ��
	virtual void drawPre(void) override;

	//! ��ü�� �׸���
	virtual void drawDo(void) override;

	//! ��ü�� �׸� ��
	virtual void drawPost(void) override;

public:

	boxObject(void);

	virtual ~boxObject(void);

public:

	LPD3DXMESH & getMesh(void) { return m_pWallMesh; }
private:

	//! �� �޽��� �����Ѵ�
	LPD3DXMESH createWallMesh(void);

private:

	LPD3DXMESH m_pWallMesh = nullptr;
};