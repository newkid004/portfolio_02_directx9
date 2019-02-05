#pragma once
#include "kGlobalDefine.h"
#include "renderObject.h"
#include "allocateHierarchy.h"

class animationController;

class skinnedMesh : public renderObject
{
public :
	struct mParam
	{
		string filePath;
		string effectFilePath;
	};

private :
	LPD3DXMESH _mesh = nullptr;
	LPD3DXEFFECT _effect = nullptr;

	string _basePath = "";
	mParam _param = { 0 };

	allocateHierarchy::boneFrame* _rootBone = nullptr;
	vector<allocateHierarchy::meshContainer*> _vMeshContainerList;

	animationController* _aniController = nullptr;

public :
	void update(void) override;

protected :
	void drawPre(void) override;
	void drawDo(void) override;
	void drawPost(void) override;

private :

	// 본 행렬 갱신
	void updateBoneMatrix(LPD3DXFRAME frame, const D3DXMATRIXA16 & mUpdate);

	// 정보 출력
	void drawBone(LPD3DXFRAME frame);
	void drawMeshContainer(LPD3DXFRAME frame, LPD3DXMESHCONTAINER meshContainer);

	// 본
	void setupBone(LPD3DXFRAME frame);
	void setupBoneOnMeshContainer(LPD3DXFRAME frame, LPD3DXMESHCONTAINER meshContainer);

	// 메쉬
	LPD3DXMESH createSkinnedMeshFromX(const string & filePath);
	LPD3DXMESH createSkinnedMesh(LPD3DXMESHCONTAINER meshContainer, int meshContainerNumber);

public :
	animationController* getAniController(void) { return _aniController; }
	const mParam & getMakeParam(void) { return _param; }

	LPD3DXMESH getMesh(void) { return _mesh; }

public:
	skinnedMesh(const mParam & param);
	virtual ~skinnedMesh();
};

