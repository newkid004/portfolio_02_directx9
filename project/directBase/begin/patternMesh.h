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

private:
	staticMesh * _weapon = nullptr;
	LPD3DXMESH _mesh = nullptr;
	LPD3DXMESH _cloneMesh = nullptr;
	LPD3DXEFFECT _effect = nullptr;

	std::string _basePath = "";
	mParam _param = { 0 };

	allocateHierarchy::boneFrame* _rootBone = nullptr;
	std::vector<allocateHierarchy::meshContainer*> _vMeshContainerList;

	animationControllerDigit* _aniControllerDigit = nullptr;

	std::vector<D3DXVECTOR4> _vVertexList;

	int num = 0;
	int _leftFingerNumber = -1;
	int _rightFingerNumber = -1;
	bool _IsleftHand = true;
public:
	void update(void) override;
	int findFinger(void);

protected:
	void drawPre(void) override;
	void drawDo(void) override;
	void drawPost(void) override;

public:
	void drawpreMesh(ACInfo& acInfo);

	void setWeapon(staticMesh* weapon);

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

	// 메쉬
	LPD3DXMESH createSkinnedMeshFromX(const std::string & filePath);
	LPD3DXMESH createSkinnedMesh(LPD3DXMESHCONTAINER meshContainer, int meshContainerNumber);

public:
	animationControllerDigit * getAniController(void) { return _aniControllerDigit; }
	mParam & getMakeParam(void) { return _param; }

	std::string & getBasePath(void) { return _basePath; }
	LPD3DXMESH getMesh(void) { return _mesh; }
	LPD3DXEFFECT getEffect(void) { return _effect; }
public:
	patternMesh(const mParam & param);
	virtual ~patternMesh();
};

