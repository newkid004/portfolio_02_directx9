#include "allocateHierarchy.h"

#include "managerList.h"
#include "gFunc.h"

allocateHierarchy::allocateHierarchy(const mParam & param) :
	_param(param)
{
}

allocateHierarchy::~allocateHierarchy()
{
}

HRESULT allocateHierarchy::CreateFrame(LPCSTR Name, LPD3DXFRAME * ppNewFrame)
{
	auto result = new boneFrame();

	if (Name != nullptr)
	{
		result->Name = (char*)malloc(sizeof(char) * (strlen(Name) + 1));
		strcpy(result->Name, Name);
	}

	D3DXMatrixIdentity(&result->combineMatrix);
	D3DXMatrixIdentity(&result->TransformationMatrix);

	*ppNewFrame = result;

	return S_OK;
}

HRESULT allocateHierarchy::CreateMeshContainer(
	LPCSTR Name, 
	CONST D3DXMESHDATA * pMeshData, 
	CONST D3DXMATERIAL * pMaterials,
	CONST D3DXEFFECTINSTANCE * pEffectInstances,
	DWORD NumMaterials, 
	CONST DWORD * pAdjacency,
	LPD3DXSKININFO pSkinInfo, 
	LPD3DXMESHCONTAINER * ppNewMeshContainer)
{
	auto result = new meshContainer;

	if (pMeshData->Type == D3DXMESHDATATYPE::D3DXMESHTYPE_MESH)
	{
		// MeshData�� �޽� ��ü�� �Լ� ȣ���� �Ϸ�ǰ� ���� Release�Լ��� ȣ��Ǳ� ������
		// �ش� �޽� ��ü�� ��� ����ϱ� ���ؼ� AddRef �Լ��� ����
		// ���۷��� ī��Ʈ�� �������� ��� ��
		result->MeshData = *pMeshData;
		result->MeshData.pMesh->AddRef();

		// ���� ���� ����
		result->pAdjacency = (DWORD*)malloc(sizeof(DWORD) * (pMeshData->pMesh->GetNumFaces() * 3));
		CopyMemory(result->pAdjacency, pAdjacency, sizeof(DWORD) * (pMeshData->pMesh->GetNumFaces() * 3));

		// �޽� �����̳� �̸��� ���� ���
		if (Name != nullptr)
		{
			result->Name = (char*)malloc(sizeof(char) * (strlen(Name) + 1));
			strcpy(result->Name, Name);
		}

		// ���� ���� ����
		result->NumMaterials = NumMaterials;
		result->pMaterials = (LPD3DXMATERIAL)malloc(sizeof(D3DXMATERIAL) * NumMaterials);
		CopyMemory(result->pMaterials, pMaterials, sizeof(D3DXMATERIAL) * NumMaterials);

		for (int i = 0; i < NumMaterials; ++i)
		{
			LPDIRECT3DTEXTURE9 t = nullptr;

			if (pMaterials[i].pTextureFilename != nullptr)
			{
				char filePath[MAX_PATH] = "";
				sprintf(filePath, "%s%s", _param.basePath.c_str(), pMaterials[i].pTextureFilename);

				t = MN_SRC->getTexture(filePath);
			}
			result->vTextureList.push_back(t);
		}

		// ��Ų ���� ����
		if (pSkinInfo != nullptr)
		{
			result->pSkinInfo = pSkinInfo;
			result->pSkinInfo->AddRef();

			for (int i = 0; i < pSkinInfo->GetNumBones(); ++i)
			{
				D3DXMATRIXA16 m = *pSkinInfo->GetBoneOffsetMatrix(i);
				result->vBoneMatrixList.push_back(m);
			}
			++_meshContainerNumber;
			result->pSkinndMesh = _param.skinnedMeshCreator(result, _meshContainerNumber);
		}
	}

	*ppNewMeshContainer = result;

	return S_OK;
}

HRESULT allocateHierarchy::DestroyFrame(LPD3DXFRAME pFrameToFree)
{
	SAFE_FREE(pFrameToFree->Name);
	SAFE_DELETE(pFrameToFree);

	return S_OK;
}

HRESULT allocateHierarchy::DestroyMeshContainer(LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	auto del = (meshContainer*)pMeshContainerToFree;

	SAFE_FREE(del->Name);
	SAFE_FREE(del->pAdjacency);
	SAFE_FREE(del->pMaterials);

	SAFE_RELEASE(del->pSkinndMesh);
	SAFE_RELEASE(del->pSkinInfo);
	SAFE_RELEASE(del->MeshData.pMesh);

	SAFE_DELETE(del);

	return S_OK;
}