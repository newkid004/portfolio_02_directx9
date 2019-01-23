#pragma once
#include "kGlobalDefine.h"

// ���� ���� �Ҵ���

/*
	ID3DXAllocateHierarchy Ŭ������ �߻� Ŭ�����̱� ������ �𵨸��� �̷��
	���� �޽��� ������ ���������� ���� �� ���� ������ �����ؾ� ��
*/

using namespace std;

class allocateHierarchy : public ID3DXAllocateHierarchy
{
public :
	// �� ������
	struct boneFrame : public D3DXFRAME
	{
		D3DXMATRIXA16 combineMatrix;	// ���� ��ȯ ���
	};
	
	// �޽� �����̳�
	struct meshContainer : public D3DXMESHCONTAINER
	{
		DWORD numBlends;
		LPD3DXMESH pSkinndMesh;

		vector<boneFrame*> vBoneList;
		vector<D3DXMATRIXA16> vBoneMatrixList;
		vector<LPDIRECT3DTEXTURE9> vTextureList;
		vector<D3DXBONECOMBINATION> vBoneCombinationList;
	};

	// �Ű� ����
	struct mParam
	{
		string basePath;
		function<LPD3DXMESH(LPD3DXMESHCONTAINER, int)> skinnedMeshCreator;
	};

private :
	mParam _param = { 0 };
	int _meshContainerNumber = 0;

public :	// �������̽� : ID3DXAllocateHierarchy
	// �� ������ ����
	virtual HRESULT CALLBACK CreateFrame(LPCSTR Name, LPD3DXFRAME *ppNewFrame) override;

	// �޽� ����
	virtual HRESULT CALLBACK CreateMeshContainer(
		LPCSTR Name,
		CONST D3DXMESHDATA *pMeshData,
		CONST D3DXMATERIAL *pMaterials,
		CONST D3DXEFFECTINSTANCE *pEffectInstances,
		DWORD NumMaterials,
		CONST DWORD *pAdjacency,
		LPD3DXSKININFO pSkinInfo,
		LPD3DXMESHCONTAINER *ppNewMeshContainer) override;

	// �� ������ ����
	virtual HRESULT CALLBACK DestroyFrame(LPD3DXFRAME pFrameToFree) override;

	// �޽� ����
	virtual HRESULT CALLBACK DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerToFree) override;

public:
	allocateHierarchy(const mParam & param);
	~allocateHierarchy();
};

