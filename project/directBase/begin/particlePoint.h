#pragma once
#include "kGlobalDefine.h"
#include "particleSystem.h"

class particlePoint : public particleSystem
{
public:
	struct vertex
	{
		enum { FVF = D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE };
		D3DXVECTOR3 position;
		float pSize = 1.0f;
		D3DCOLOR diffuse = COLOR_BLACK(255);
	};

protected:
	virtual void drawPre(void) override;
	virtual void drawDo(void) override;
	virtual void drawPost(void) override;

private:
	static LPDIRECT3DVERTEXBUFFER9 createVertexBuffer(const particleSystem::mParams & param);

public:
	particlePoint(const particleSystem::mParams & param);
	virtual ~particlePoint();
};

