#pragma once
#include "kGlobalDefine.h"
#include "staticMesh.h"

class aStar_node;

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

	float _planeRadius = 1.0f;
	LPD3DXMESH _plane = nullptr;

	D3DXMATRIXA16 _mWorldPlane;

	aStar_node* _bindNode = nullptr;

public :
	virtual void update(void) override;
	virtual void drawDo(void) override;

public :
	const D3DXVECTOR4 & getNodeColor(void) { return _nodeColor; }
	float getPlaneRadius(void) { return _planeRadius; }
	aStar_node* getBindNode(void) { return _bindNode; }

	void setNodeColor(const D3DXVECTOR4 & input) { _nodeColor = input; }
	void setPlaneRadius(float input) { _planeRadius = input; }
	void setBindNode(aStar_node* input) { _bindNode = input; }

private :
	LPD3DXMESH createPlane(void);

public:
	nodeMesh(const mParam & param);
	~nodeMesh();
};

