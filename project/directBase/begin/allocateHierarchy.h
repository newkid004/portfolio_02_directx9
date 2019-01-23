#pragma once
#include "kGlobalDefine.h"

// 계층 구조 할당자

/*
	ID3DXAllocateHierarchy 클래스는 추상 클래스이기 때문에 모델링을 이루는
	본과 메쉬의 정보는 직접적으로 생성 및 제거 로직을 구현해야 함
*/

using namespace std;

class allocateHierarchy : public ID3DXAllocateHierarchy
{
public :
	// 본 프레임
	struct boneFrame : public D3DXFRAME
	{
		D3DXMATRIXA16 combineMatrix;	// 최종 변환 행렬
	};
	
	// 메쉬 컨테이너
	struct meshContainer : public D3DXMESHCONTAINER
	{
		DWORD numBlends;
		LPD3DXMESH pSkinndMesh;

		vector<boneFrame*> vBoneList;
		vector<D3DXMATRIXA16> vBoneMatrixList;
		vector<LPDIRECT3DTEXTURE9> vTextureList;
		vector<D3DXBONECOMBINATION> vBoneCombinationList;
	};

	// 매개 변수
	struct mParam
	{
		string basePath;
		function<LPD3DXMESH(LPD3DXMESHCONTAINER, int)> skinnedMeshCreator;
	};

private :
	mParam _param = { 0 };
	int _meshContainerNumber = 0;

public :	// 인터페이스 : ID3DXAllocateHierarchy
	// 본 프레임 생성
	virtual HRESULT CALLBACK CreateFrame(LPCSTR Name, LPD3DXFRAME *ppNewFrame) override;

	// 메쉬 생성
	virtual HRESULT CALLBACK CreateMeshContainer(
		LPCSTR Name,
		CONST D3DXMESHDATA *pMeshData,
		CONST D3DXMATERIAL *pMaterials,
		CONST D3DXEFFECTINSTANCE *pEffectInstances,
		DWORD NumMaterials,
		CONST DWORD *pAdjacency,
		LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer) override;

	// 본 프레임 제거
	virtual HRESULT CALLBACK DestroyFrame(LPD3DXFRAME pFrameToFree) override;

	// 메쉬 제거
	virtual HRESULT CALLBACK DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerToFree) override;

public:
	allocateHierarchy(const mParam & param);
	~allocateHierarchy();
};

