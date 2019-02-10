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
		std::string filePath;
		std::string effectFilePath;
	};

protected :
	LPD3DXMESH _mesh = nullptr;
	LPD3DXEFFECT _effect = nullptr;

	std::string _basePath = "";
	mParam _param = { 0 };

	allocateHierarchy::boneFrame* _rootBone = nullptr;
	std::vector<allocateHierarchy::meshContainer*> _vMeshContainerList;
	std::vector<allocateHierarchy::meshContainer*> _vMeshContainerList2;

	animationController* _aniController = nullptr;

public :
	void update(void) override;

protected :
	void drawPre(void) override;
	void drawDo(void) override;
	void drawPost(void) override;

public :
	void updateBoneMatrix(void);

private :
	// �� ��� ����
	void updateBoneMatrix(LPD3DXFRAME frame, const D3DXMATRIXA16 & mUpdate);

	// ���� ���
	void drawBone(LPD3DXFRAME frame);
	void drawMeshContainer(LPD3DXFRAME frame, LPD3DXMESHCONTAINER meshContainer);

	// ��
	void setupBone(LPD3DXFRAME frame);
	void setupBoneOnMeshContainer(LPD3DXFRAME frame, LPD3DXMESHCONTAINER meshContainer);

	// �޽�
	LPD3DXMESH createSkinnedMeshFromX(const std::string & filePath);
	LPD3DXMESH createSkinnedMesh(LPD3DXMESHCONTAINER meshContainer, int meshContainerNumber);

public :
	animationController* getAniController(void) { return _aniController; }
	mParam & getMakeParam(void) { return _param; }

	std::string & getBasePath(void) { return _basePath; }
	LPD3DXMESH getMesh(void) { return _mesh; }
	LPD3DXEFFECT getEffect(void) { return _effect; }

public:
	skinnedMesh(const mParam & param);
	virtual ~skinnedMesh();
};

