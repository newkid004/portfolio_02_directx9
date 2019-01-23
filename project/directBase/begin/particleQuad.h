#pragma once
#include "kGlobalDefine.h"
#include "particleSystem.h"

class particleQuad : public particleSystem
{
public:
	struct vertex
	{
		enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 };
		D3DXVECTOR3 position;
		D3DCOLOR diffuse;
		D3DXVECTOR2 uv;
	};

private:
	LPDIRECT3DVERTEXDECLARATION9 _vertexDec = nullptr;

protected:
	virtual void drawPre(void) override;
	virtual void drawDo(void) override;
	virtual void drawPost(void) override;

private:
	LPDIRECT3DVERTEXDECLARATION9 createVertexDec(void);
	static LPDIRECT3DVERTEXBUFFER9 createVertexBuffer(const particleSystem::mParams & param);

public:
	particleQuad(const particleSystem::mParams & param);
	~particleQuad();
};