#pragma once
#include "kGlobalDefine.h"
#include "renderObject.h"

class charaterArea :public renderObject
{
	struct vertex
	{
		enum
		{
			FVF = D3DFVF_XYZ | D3DFVF_TEX1
		};
		D3DXVECTOR3 m_stPosition;
		D3DXVECTOR2 m_stUV;
	};

private:
	int _length = 0;
	LPDIRECT3DVERTEXBUFFER9 _vertexBuffer = nullptr;
	LPDIRECT3DTEXTURE9 _texture = nullptr;

#ifdef _DEBUG
private:
	virtual void update(void) override;
	virtual void drawPre(void) override;
	virtual void drawDo(void) override;
	virtual void drawPost(void) override;

#endif

private:
	LPDIRECT3DVERTEXBUFFER9 createVertexBuffer(void);
public:
	void setLength(int length) { _length = length; }

public:
	charaterArea(int length);
	virtual ~charaterArea();
};