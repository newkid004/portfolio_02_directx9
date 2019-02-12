#pragma once
#include "kGlobalDefine.h"
#include "staticMesh.h"

class nodeMesh : public staticMesh
{
public :
	struct vertex
	{
		enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
		D3DXVECTOR3 pos;
		D3DXVECTOR2 uv;
	};

protected :
	D3DXVECTOR4 _nodeColor = D3DXVECTOR4(1, 1, 1, 1);

	float _planeScale = 1.0f;
	LPD3DXMESH _plane = nullptr;

	D3DXMATRIXA16 _mWorldPlane;

public :
	virtual void update(void) override;
	virtual void drawDo(void) override;

public :
	const D3DXVECTOR4 & getNodeColor(void) { return _nodeColor; }
	float getPlaneScale(void) { return _planeScale; };

	void setNodeColor(const D3DXVECTOR4 & input) { _nodeColor = input; }
	void setPlaneScale(float input) { _planeScale = input; }

private :
	LPD3DXMESH createPlane(void);

public:
	nodeMesh(const mParam & param);
	~nodeMesh();
};

