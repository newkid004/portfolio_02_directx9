#pragma once
#include "kGlobalDefine.h"
#include "renderObject.h"

class debugGrid : public renderObject
{
public :
	struct vertex
	{
		enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };

		D3DXVECTOR3 pos;
		D3DCOLOR diffuse;
	};

private :
	int _size = 0;
	LPDIRECT3DVERTEXBUFFER9 _vertexBuffer = nullptr;

protected :	// interface
	virtual void drawPre(void) override;
	virtual void drawDo(void) override;
	virtual void drawPost(void) override;

private :
	LPDIRECT3DVERTEXBUFFER9  createVertexBuffer(void);

public:
	debugGrid(int size);
	~debugGrid();
};

