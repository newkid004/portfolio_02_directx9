#pragma once
#include "kGlobalDefine.h"
#include "renderObject.h"
#include "allocateHierarchy.h"
#include "AnimationDef.h"

class animationControllerDigit;
class staticMesh;

class patternMesh : public renderObject
{
public:
	struct type
	{
		static constexpr int survivor = 0;
		static constexpr int male_zombie = 1;
		static constexpr int feMale_zombie = 2;
		static constexpr int hulk_zombie = 3;
	};

	struct mParam
	{
		std::string filePath;
		std::string effectFilePath;
	};

	struct STVertex
	{
		D3DXVECTOR3 m_stPosition;
		D3DXVECTOR3 m_stNormal;
		D3DXVECTOR3 m_stBinormal;
		D3DXVECTOR3 m_stTangent;
		D3DXVECTOR2 m_stUV;
		D3DXVECTOR4 m_stBlendWeight;
	};

	struct STBoneInfo
	{
		D3DXVECTOR3 position;
		D3DXMATRIXA16 matrix;
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
private:
	int _originType;
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

	ECharacterType _characterType = ECharacterType::NONE;

	animationControllerDigit* _aniControllerDigit = nullptr;

	std::vector<D3DXVECTOR4> _vVertexList;
	D3DXMATRIXA16 _handMatrix[2];
	D3DXMATRIXA16 _neckMatrix;

	int num = 0;
	int _leftFingerNumber = -1;
	int _rightFingerNumber = -1;
	int _neckNumber = -1;
public:
	void init(void);
	void update(void) override;
	void findPart(const char* partName, int& partNumber);
	void setupBoneInfo(std::string name, BYTE width, BYTE height, BYTE depth);
protected:
	void drawPre(void) override;
	void drawDo(void) override;
	void drawPost(void) override;

public:
	void drawpreMesh(ACInfo& acInfo);

private:
	// 본 행렬 갱신
	void updateBoneMatrix(LPD3DXFRAME frame, const D3DXMATRIXA16 & mUpdate);

	// 정보 출력
	void drawBone(LPD3DXFRAME frame);
	void drawMeshContainer(LPD3DXFRAME frame, LPD3DXMESHCONTAINER meshContainer);
	//void drawBox(void);

	// 본
	void setupBone(LPD3DXFRAME frame);
	void setupBoneOnMeshContainer(LPD3DXFRAME frame, LPD3DXMESHCONTAINER meshContainer);

	// 바운딩 박스 셋업
	void setBoneBoundBox(void);
	void setBoneBoundSphere(void);

	// 메쉬
	LPD3DXMESH createSkinnedMeshFromX(const std::string & filePath);
	LPD3DXMESH createSkinnedMesh(LPD3DXMESHCONTAINER meshContainer, int meshContainerNumber);

public:
	animationControllerDigit * getAniController(void) { return _aniControllerDigit; }
	mParam & getMakeParam(void) { return _param; }
	constexpr int &getOriginType(void) { return _originType; }

	std::string & getBasePath(void) { return _basePath; }
	LPD3DXMESH getMesh(void) { return _mesh; }
	LPD3DXEFFECT getEffect(void) { return _effect; }
	D3DXMATRIXA16 &getHandMatrix(int index) { return _handMatrix[index]; }
	D3DXMATRIXA16 &getNeckMatrix(void) { return _neckMatrix; }
	BONEINFOLIST &getBoneInfoList(void) { return _mBoneInfoList; }
public:
	patternMesh(const mParam & param, ECharacterType characterType = ECharacterType::NONE);
	virtual ~patternMesh();
};

