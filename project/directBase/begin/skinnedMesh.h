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

	struct STBoneInfo
	{
		D3DXVECTOR3 position;
		D3DXMATRIXA16 combineMatrix;
	};

	struct STBoxSize
	{
		BYTE width;
		BYTE height;
		BYTE depth;
	};

	typedef std::unordered_map<std::string, STBoneInfo> BONEINFOLIST;
	typedef std::unordered_map<std::string, STBoxSize> BOXSIZELIST;

protected :
	LPD3DXMESH _mesh = nullptr;
	LPD3DXMESH _cloneMesh = nullptr;
	LPD3DXEFFECT _effect = nullptr;

	std::string _basePath = "";
	mParam _param = { 0 };

	allocateHierarchy::boneFrame* _rootBone = nullptr;
	std::vector<allocateHierarchy::meshContainer*> _vMeshContainerList;

	BONEINFOLIST _mBoneInfoList;
	BOXSIZELIST _mBoxSizeList;
	std::vector<std::string> _vBoneNameList;

	animationController* _aniController = nullptr;

	ECharacterType _characterType = ECharacterType::NONE;


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
	void setBoneBoundBox(void);
	void setBoneBoundSphere(void);

	// 메쉬
	LPD3DXMESH createSkinnedMeshFromX(const std::string & filePath);
	LPD3DXMESH createSkinnedMesh(LPD3DXMESHCONTAINER meshContainer, int meshContainerNumber);

public :

	void setupBoneInfo(std::string name, const D3DXVECTOR3 & position, BYTE width, BYTE height, BYTE depth);

	animationController* getAniController(void) { return _aniController; }
	mParam & getMakeParam(void) { return _param; }

	std::string & getBasePath(void) { return _basePath; }
	LPD3DXMESH getMesh(void) { return _mesh; }
	LPD3DXEFFECT getEffect(void) { return _effect; }

public:
	skinnedMesh(const mParam & param, ECharacterType characterType = ECharacterType::NONE);
	virtual ~skinnedMesh();
};

