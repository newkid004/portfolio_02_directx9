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
		// MeshData의 메쉬 객체는 함수 호출이 완료되고 나면 Release함수가 호출되기 때문에
		// 해당 메쉬 객체를 계속 사용하기 위해선 AddRef 함수를 통해
		// 레퍼런스 카운트를 증가시켜 줘야 함
		result->MeshData = *pMeshData;
		result->MeshData.pMesh->AddRef();

		// 인접 정보 설정
		result->pAdjacency = (DWORD*)malloc(sizeof(DWORD) * (pMeshData->pMesh->GetNumFaces() * 3));
		CopyMemory(result->pAdjacency, pAdjacency, sizeof(DWORD) * (pMeshData->pMesh->GetNumFaces() * 3));

		// 메쉬 컨테이너 이름이 있을 경우
		if (Name != nullptr)
		{
			result->Name = (char*)malloc(sizeof(char) * (strlen(Name) + 1));
			strcpy(result->Name, Name);
		}

		// 재질 정보 설정
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

		// 스킨 정보 설정
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