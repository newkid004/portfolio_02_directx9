#pragma once

#include "kGlobalDefine.h"
#include "renderObject.h"

class debugDraw : public renderObject
{
public:
	struct vertex
	{
		enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
		D3DXVECTOR3 pos;
		D3DXCOLOR diffuse;
	};

private:
	LPD3DXMESH _meshBoundingBox = nullptr;
	LPD3DXMESH _meshBoundingSphere = nullptr;
	std::vector<LPD3DXMESH> _vMeshBoundingBoxList;
	std::vector<LPD3DXMESH> _vMeshBoundingSphereList;
	std::unordered_map<std::string, LPD3DXMESH> _mMeshBoundingBoxSetList;
	std::unordered_map<std::string, LPD3DXMESH> _mMeshBoundingSphereSetList;

	renderObject* _bindObject = nullptr;
	EDebugDrawType _drawType;

protected:
	virtual void drawPre(void) override;
	virtual void drawDo(void) override;
	virtual void drawPost(void) override;

private:
	void updateBoundingMatrix(void);

	void drawBoundingBox(void);
	void drawBoundingSphere(void);

	void drawGuideLine(void);
	void drawGuideLineBox(void);

	LPD3DXMESH createBoundingSphere(boundingSphere & input);
	void createBoundingBox(std::vector<boundingBox> & input);
	void createBoundingBox(BOUNDBOXMATRIXSET & input);
	void createBoundingSphere(std::vector<boundingSphere> & input);
	void createBoundingSphere(BOUNDSPHEREMATRIXSET & input);

public:
	LPD3DXMESH getBoundMesh(EDebugDrawType type = EDebugDrawType::NONE);
	void getMatrixBound(D3DXMATRIXA16 * outMat, EDebugDrawType type = EDebugDrawType::NONE);
	void getMatrixBound(int index, D3DXMATRIXA16 * outMat, EDebugDrawType type = EDebugDrawType::NONE);
	void getMatrixBound(std::string name, D3DXMATRIXA16 * outMat, D3DXMATRIXA16 & combineMat, EDebugDrawType type = EDebugDrawType::NONE);
public:
	debugDraw(renderObject* bind, EDebugDrawType drawType);
	~debugDraw();
};

