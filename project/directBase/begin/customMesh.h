#pragma once
#include "kGlobalDefine.h"
#include "renderObject.h"

class customMesh : public renderObject
{
public :
	struct vertexSphere
	{
		enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 };
		D3DXVECTOR3 pos;
		D3DXVECTOR4 color;
		D3DXVECTOR2 uv;
	};

private :
	LPD3DXMESH _meshSphere	= nullptr;
	LPD3DXMESH _meshPlane	= nullptr;

public :
	virtual void drawPre(void);
	virtual void drawDo(void);
	virtual void drawPost(void);

public :
	LPD3DXMESH & getMesh(void) { return _meshSphere; }

private :
	LPD3DXMESH createMeshSphere(void);
	LPD3DXMESH createMeshPlane(void);

public:
	customMesh();
	~customMesh();
};

