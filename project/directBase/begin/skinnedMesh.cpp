#include "skinnedMesh.h"

#include "camera.h"
#include "direct3dApplication.h"
#include "gFunc.h"
#include "managerList.h"
#include "animationController.h"

#include "lightBase.h"

#include "sceneBase.h"

#define SKINNED_MESH_TYPE_DEVICE	1
#define SKINNED_MESH_TYPE_SHADER	2
#define SKINNED_MESH_TYPE			SKINNED_MESH_TYPE_SHADER

using namespace std;
skinnedMesh::skinnedMesh(const mParam & param, ECharacterType characterType) :
	_param(param),
	_characterType(characterType)
{
	if (param.filePath.rfind("/") != string::npos)
		_basePath = param.filePath.substr(0, param.filePath.rfind("/") + 1);

	_effect = MN_SRC->getEffect(param.effectFilePath);
	_mesh = createSkinnedMeshFromX(param.filePath);

}

skinnedMesh::~skinnedMesh()
{
	SAFE_DELETE(_aniController);
}

void skinnedMesh::init(void)
{
	this->setBoundBox();
}

void skinnedMesh::update(void)
{
	renderObject::update();

	_aniController->update();

	updateBoneMatrix(_rootBone, getMatrixFinal());
}

void skinnedMesh::drawPre(void)
{
	renderObject::drawPre();

#if SKINNED_MESH_TYPE == SKINNED_MESH_TYPE_SHADER
	_effect->SetMatrix("_mView", &GET_CAMERA()->getMatrixView());
	_effect->SetMatrix("_mProjection", &GET_CAMERA()->getMatrixProjection());
	_effect->SetMatrix("_mViewProjection", &GET_CAMERA()->getMatrixViewProjection());

	D3DXVECTOR4 viewPosition(GET_CAMERA()->getPosition(), 1.0f);
	_effect->SetVector("_viewPosition", &viewPosition);

	D3DXVECTOR4 lightDirection(GET_LIGHT()->getDirectForward(), 0.0f);
	D3DXVec4Normalize(&lightDirection, &lightDirection);
	_effect->SetVector("_lightDirection", &lightDirection);

#endif	// SKINNED_MESH_TYPE == SKINNED_MESH_TYPE_SHADER

	MN_DEV->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
}

void skinnedMesh::drawDo(void)
{
	renderObject::drawDo();

	drawBone(_rootBone);
}

void skinnedMesh::drawPost(void)
{
	renderObject::drawPost();
	MN_DEV->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
#if SKINNED_MESH_TYPE == SKINNED_MESH_TYPE_DEVICE
	MN_DEV->SetTexture(0, NULL);
#endif // SKINNED_MESH_TYPE == SKINNED_MESH_TYPE_DEVICE
}

void skinnedMesh::updateBoneMatrix(void)
{
	updateBoneMatrix(_rootBone, getMatrixFinal());
}

void skinnedMesh::updateBoneMatrix(LPD3DXFRAME frame, const D3DXMATRIXA16 & mUpdate)
{
	auto bone = (allocateHierarchy::boneFrame*)frame;

	bone->combineMatrix = bone->TransformationMatrix * mUpdate;
	
	// 컴바인 매트릭스 복사
	if (bone->Name != NULL)
	{
		if (_vBoneInfoList.find(bone->Name) != _vBoneInfoList.end())
		{
			_vBoneInfoList.find(bone->Name)->second.combineMatrix = bone->combineMatrix;
		}
	}
	
	//setBoundMatrix(bone->Name, bone->combineMatrix);

	// 연관 본 갱신
	if (bone->pFrameSibling != nullptr)		updateBoneMatrix(bone->pFrameSibling, mUpdate);
	if (bone->pFrameFirstChild != nullptr)	updateBoneMatrix(bone->pFrameFirstChild, bone->combineMatrix);
}

void skinnedMesh::drawBone(LPD3DXFRAME frame)
{
	auto meshCont = frame->pMeshContainer;

	while (meshCont != nullptr)
	{
		drawMeshContainer(frame, meshCont);

		meshCont = meshCont->pNextMeshContainer;
	}

	// 형제 본 정보가 있을 경우
	if (frame->pFrameSibling != nullptr)
		drawBone(frame->pFrameSibling);

	// 자식 본 정보가 있을 경우
	if (frame->pFrameFirstChild != nullptr)
		drawBone(frame->pFrameFirstChild);
}

void skinnedMesh::drawMeshContainer(LPD3DXFRAME frame, LPD3DXMESHCONTAINER meshContainer)
{
	if (meshContainer->pSkinInfo == nullptr) return;


#if SKINNED_MESH_TYPE == SKINNED_MESH_TYPE_DEVICE
	// 디바이스를 이용한 최대 뼈대 가중치 연산은 그래픽 카드 지원 여부에 종속되기 때문에 미리 검사가 필요
	D3DCAPS9 devCaps;
	GET_DEVICE_MANAGER()->getDirect3D()->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &devCaps);
	
	auto meshCont = (allocateHierarchy::meshContainer*)meshContainer;

	for (int i = 0; i < meshCont->vBoneCombinationList.size(); ++i)
	{
		int numBlends = 0;
		auto boneComb = meshCont->vBoneCombinationList[i];

		// 뼈대 가중치 연산 횟수 탐색
		for (int j = 0; j < meshCont->numBlends; ++j)
		{
			// 본 조합 정보의 값은 UINT_MAX가 아닐 경우 뼈대 가중치에 영향을 받는 정보가 있다는 것을 의미
			if (boneComb.BoneId[j] != UINT_MAX)
				numBlends = j;
		}
		
		// 그래픽 카드에서 지원하는 최대 뼈대 가중치 연산 횟수가 적합한 경우
		if (numBlends < devCaps.MaxVertexBlendMatrices)
		{
			for (int j = 0; j < meshCont->numBlends; ++j)
			{
				int boneID = boneComb.BoneId[j];

				if (boneID != UINT_MAX)
				{
					auto bone = meshCont->vBoneList[boneID];
					D3DXMATRIXA16 mBone = meshCont->vBoneMatrixList[boneID];
					D3DXMATRIXA16 mWorld = mBone * bone->combineMatrix;

					MN_DEV->SetTransform(D3DTS_WORLDMATRIX(j), &mWorld);
				}
			}
			// 텍스쳐 설정
			int attributeID = boneComb.AttribId;
			MN_DEV->SetTexture(0, meshCont->vTextureList[attributeID]);
			MN_DEV->SetRenderState(D3DRS_VERTEXBLEND, numBlends);	// 뼈대 가중치 연산 활성화(참고하게 될 월드 행렬 개수)

			meshCont->pSkinndMesh->DrawSubset(i);
		}
	}
	// 뼈대 가중치 연산 비활성화
	MN_DEV->SetRenderState(D3DRS_VERTEXBLEND, 0);

#else
	auto meshCont = (allocateHierarchy::meshContainer*)meshContainer;
	for (int i = 0; i < meshCont->vBoneCombinationList.size(); ++i)
	{
		int numBlends = 0;
		auto boneComb = meshCont->vBoneCombinationList[i];
		
		// 뼈대 가중치 연산 횟수 탐색
		for (int j = 0; j < meshCont->numBlends; ++j)
		{
			if (boneComb.BoneId[j] != UINT_MAX)
				numBlends = j;
		}

		D3DXMATRIXA16 mWorld[4];
		for (int j = 0; j < 4; ++j)
			D3DXMatrixIdentity(mWorld + j);

		for (int j = 0; j < meshCont->numBlends; ++j)
		{
			int boneID = boneComb.BoneId[j];

			if (boneID != UINT_MAX)
			{
				auto bone = meshCont->vBoneList[boneID];
				D3DXMATRIXA16 mBone = meshCont->vBoneMatrixList[boneID];

				mWorld[j] = mBone * bone->combineMatrix;
			}
		}
		
		_effect->SetInt("_numBlend", numBlends);
		_effect->SetMatrixArray("_mWorld", mWorld, 4);

		int attributeID = boneComb.AttribId;
		_effect->SetTexture("_texture", meshCont->vTextureList[attributeID]);
		if (meshCont->vNormalTextureList[attributeID] != nullptr)
		{
			_effect->SetTexture("_normalTexture", meshCont->vNormalTextureList[attributeID]);
		}

		gFunc::runEffectLoop(_effect, "myTechnique", [&](int passNum)->void {
			meshCont->pSkinndMesh->DrawSubset(i);
		});
	}
	
#endif // SKINNED_MESH_TYPE == SKINNED_MESH_TYPE_DEVICE
}

void skinnedMesh::setBoundBox(void)
{
	switch (_characterType)
	{
	case ECharacterType::NORMAL_ZOMBIE:
	{
		for (int i = 0; i < _vBoneNameList.size(); ++i)
		{
			if (_vBoneInfoList.find(_vBoneNameList[i]) != _vBoneInfoList.end())
			{
				D3DXVec3TransformCoord(&_vBoneInfoList.find(_vBoneNameList[i])->second.position,
					&_vBoneInfoList.find(_vBoneNameList[i])->second.position,
					&_vBoneInfoList.find(_vBoneNameList[i])->second.combineMatrix);

				//setBoundingBox(_vBoneNameList[i], gFunc::createBoundingBox(
				//	this->getPosition() + _vBoneInfoList.find(_vBoneNameList[i])->second.position,
				//	3, 3, 3));
			}
		}
	}
	}
}

void skinnedMesh::setupBone(LPD3DXFRAME frame)
{
	if (frame->pMeshContainer != nullptr)
		setupBoneOnMeshContainer(frame, frame->pMeshContainer);

	// 형제 본 정보
	if (frame->pFrameSibling != nullptr)
		setupBone(frame->pFrameSibling);

	// 자식 본 정보
	if (frame->pFrameFirstChild != nullptr)
		setupBone(frame->pFrameFirstChild);
}

void skinnedMesh::setupBoneInfo(string name, const D3DXVECTOR3 & position)
{
	switch (_characterType)
	{
		case ECharacterType::NORMAL_ZOMBIE:
		{
			BoneInfo boneInfo;
			ZeroMemory(&boneInfo, sizeof(boneInfo));

			boneInfo.position = position;
			for (int i = 0; i < _vMeshContainerList.size(); ++i)
			{
				for (int j = 0; j < _vMeshContainerList[i]->vBoneList.size(); ++j)
				{
					if (_vMeshContainerList[i]->vBoneList[j]->Name == string(name))
					{
						boneInfo.combineMatrix = _vMeshContainerList[i]->vBoneList[j]->combineMatrix;
					}
				}
			}
			_vBoneInfoList.insert(map<string, BoneInfo>::value_type(name, boneInfo));
			_vBoneNameList.push_back(name);
		}
	}
}

void skinnedMesh::setupBoneOnMeshContainer(LPD3DXFRAME frame, LPD3DXMESHCONTAINER meshContainer)
{
	auto meshCont = (allocateHierarchy::meshContainer*)meshContainer;

	if (meshCont->pSkinInfo != nullptr)
	{
		int numBones = meshCont->pSkinInfo->GetNumBones();

		for (int i = 0; i < numBones; ++i)
		{
			auto boneName = meshCont->pSkinInfo->GetBoneName(i);	// 해당 본의 이름을 반환
			auto bone = D3DXFrameFind(_rootBone, boneName);			// root 본의 이름을 이용해 본을 탐색
			
			meshCont->vBoneList.push_back((allocateHierarchy::boneFrame*)bone);
		}
	}
}

LPD3DXMESH skinnedMesh::createSkinnedMeshFromX(const string & filePath)
{
	/*
		std::bind 객체를 생성 할 때는 기본적으로 함수 호출 시 넘겨지는 매개 변수를 같이 명시하는것이 원칙
		(즉, 해당 방식으로 생성된 std::bind 객체는 함수 호출 시, 항상 동일한 값이 매개 변수로 넘겨짐)

		반면, 함수 호출 시 다른 값을 매개 변수로 넘기기 위해선 std::bind 객체를 생성 할 땐
		std::placeholders 를 이용하여 가상의 매개 변수 자리를 채워줘야 함
	*/
	allocateHierarchy::mParam aParam = {
		_basePath,
		std::bind(&skinnedMesh::createSkinnedMesh, this, std::placeholders::_1, std::placeholders::_2)
	};

	allocateHierarchy aHierarchy(aParam);

	LPD3DXANIMATIONCONTROLLER aniController = nullptr;

	// 메쉬 생성
	D3DXLoadMeshHierarchyFromXA(
		filePath.c_str(),
		D3DXMESH_MANAGED,
		MN_DEV,
		&aHierarchy,
		NULL,
		(LPD3DXFRAME*)&_rootBone,	// 최상위 본
		&aniController);			// 애니메이션을 제어하기 위한 컨트롤
	
	// 애니메이션 컨트롤러 생성
	_aniController = new animationController(aniController);

	// 본 설정
	setupBone(_rootBone);

	/*
		모델링 파일의 구조에 따라 meshContainer는 N개 이상이 생성도리 수 있기 때문에
		해당 meshContainer중 첫번째 객체가 지닌 메쉬 정보를 반환
		(일반적으로 meshContainer의 첫번째가 모델링 정보의 본체에 해당)
	*/

	return _vMeshContainerList.front()->pSkinndMesh;
}

LPD3DXMESH skinnedMesh::createSkinnedMesh(LPD3DXMESHCONTAINER meshContainer, int meshContainerNumber)
{
	auto result = (allocateHierarchy::meshContainer*)meshContainer;
	
	DWORD numBlends = 0;
	DWORD numBoneCombinations = 0;

	LPD3DXMESH pMesh = nullptr;
	LPD3DXBUFFER bufBoneCombinations = nullptr;

	// 스킨드 메쉬로 변환
	result->pSkinInfo->ConvertToBlendedMesh(
		result->MeshData.pMesh,
		result->MeshData.pMesh->GetOptions() | D3DXMESHOPT_VERTEXCACHE,
		result->pAdjacency,
		result->pAdjacency,
		NULL,
		NULL,
		&numBlends,
		&numBoneCombinations,
		&bufBoneCombinations,
		&pMesh);


	D3DVERTEXELEMENT9 elements[] = {
		{ 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
		{ 0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0 },
		{ 0, 36, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0 },
		{ 0, 48, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		{ 0, 56, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0 },
		/*
			스키닝 애니메이션을 처리하기 위해선 정점 정보에 뼈대 가중치를 나타내는
			BLENDWEIGHT 시멘틱이 반드시 포함되어야 함
		*/
		D3DDECL_END()
	};

	auto originMesh = pMesh;
	originMesh->CloneMesh(
		originMesh->GetOptions(),
		elements,
		MN_DEV,
		&pMesh);

	//D3DXFrameFind
	//static_cast<AllocateHierarchy::stbone *>(pstBone)->m_stCombineMatrix

	// 법선, 접선, 종법선 정보 계산
	D3DXComputeNormals(pMesh, result->pAdjacency);
	D3DXComputeTangent(pMesh, 0, 0, 0, true, result->pAdjacency);

	// 스키닝 정보 설정
	result->numBlends = numBlends;
	auto boneCombinations = (LPD3DXBONECOMBINATION)bufBoneCombinations->GetBufferPointer();

	for (int i = 0; i < numBoneCombinations; ++i)
	{
		D3DXBONECOMBINATION  boneComb = boneCombinations[i];

		auto copiedBoneComb = boneComb;
		copiedBoneComb.BoneId = (DWORD*)malloc(sizeof(DWORD) * numBoneCombinations);

		CopyMemory(copiedBoneComb.BoneId, boneComb.BoneId, sizeof(DWORD) * numBoneCombinations);
		result->vBoneCombinationList.push_back(copiedBoneComb);
	}

	SAFE_RELEASE(originMesh);
	SAFE_RELEASE(bufBoneCombinations);

	_vMeshContainerList.push_back(result);
	return pMesh;
}
