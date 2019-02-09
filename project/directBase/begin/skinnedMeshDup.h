#pragma once
#include "kGlobalDefine.h"
#include "renderObject.h"
#include "allocateHierarchy.h"

class skinnedMesh;

class skinnedMeshDup : public renderObject
{
private :
	skinnedMesh* _bindObject = nullptr;

	// ************** º¸·ù ************** //
	float weight;
	float position;
	string track;


public:
	void update(void) override;

protected:
	void drawPre(void) override;
	void drawDo(void) override;
	void drawPost(void) override;

private:
	void updateBoneMatrix(LPD3DXFRAME frame, const D3DXMATRIXA16 & mUpdate);

	void drawBone(LPD3DXFRAME frame);
	void drawMeshContainer(LPD3DXFRAME frame, LPD3DXMESHCONTAINER meshContainer);

public:
	skinnedMesh* getBindObject(void);

	// animationController* getAniController(void) { return _aniController; }
	// LPD3DXMESH getMesh(void) { return _mesh; }


public:
	skinnedMeshDup(skinnedMesh* duplicateTarget);
	~skinnedMeshDup();
};

