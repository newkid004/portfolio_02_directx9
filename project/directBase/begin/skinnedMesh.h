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

	struct BoneInfo
	{
		D3DXVECTOR3 position;
		D3DXMATRIXA16 combineMatrix;
	};

	typedef unordered_map<string, BoneInfo> BONEINFO;

protected :
	LPD3DXMESH _mesh = nullptr;
	LPD3DXMESH _cloneMesh = nullptr;
	LPD3DXEFFECT _effect = nullptr;

	string _basePath = "";
	mParam _param = { 0 };

	allocateHierarchy::boneFrame* _rootBone = nullptr;

	vector<allocateHierarchy::meshContainer*> _vMeshContainerList;

	animationController* _aniController = nullptr;

	BONEINFO _vBoneInfoList;
	ECharacterType _characterType = ECharacterType::NONE;

	vector<string> _vBoneNameList;
	
public :
	void init(void);
	void update(void) override;

protected :
	void drawPre(void) override;
	void drawDo(void) override;
	void drawPost(void) override;

public :
	void updateBoneMatrix(void);

private :
	// 본 행렬 갱신
	void updateBoneMatrix(LPD3DXFRAME frame, const D3DXMATRIXA16 & mUpdate);

	// 정보 출력
	void drawBone(LPD3DXFRAME frame);
	void drawMeshContainer(LPD3DXFRAME frame, LPD3DXMESHCONTAINER meshContainer);

	// 본
	void setupBone(LPD3DXFRAME frame);
	void setupBoneOnMeshContainer(LPD3DXFRAME frame, LPD3DXMESHCONTAINER meshContainer);
	void setBoundBox(void);

	// 메쉬
	LPD3DXMESH createSkinnedMeshFromX(const string & filePath);
	LPD3DXMESH createSkinnedMesh(LPD3DXMESHCONTAINER meshContainer, int meshContainerNumber);

public :

	void setupBoneInfo(string name, const D3DXVECTOR3 & position);

	animationController* getAniController(void) { return _aniController; }
	mParam & getMakeParam(void) { return _param; }

	std::string & getBasePath(void) { return _basePath; }
	LPD3DXMESH getMesh(void) { return _mesh; }
	LPD3DXEFFECT getEffect(void) { return _effect; }

public:
	skinnedMesh(const mParam & param, ECharacterType characterType = ECharacterType::NONE);
	virtual ~skinnedMesh();
};

