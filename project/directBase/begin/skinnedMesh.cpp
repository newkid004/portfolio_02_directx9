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
	
	// �Ĺ��� ��Ʈ���� ����
	if (bone->Name != NULL)
	{
		if (_vBoneInfoList.find(bone->Name) != _vBoneInfoList.end())
		{
			_vBoneInfoList.find(bone->Name)->second.combineMatrix = bone->combineMatrix;
		}
	}
	
	//setBoundMatrix(bone->Name, bone->combineMatrix);

	// ���� �� ����
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

	// ���� �� ������ ���� ���
	if (frame->pFrameSibling != nullptr)
		drawBone(frame->pFrameSibling);

	// �ڽ� �� ������ ���� ���
	if (frame->pFrameFirstChild != nullptr)
		drawBone(frame->pFrameFirstChild);
}

void skinnedMesh::drawMeshContainer(LPD3DXFRAME frame, LPD3DXMESHCONTAINER meshContainer)
{
	if (meshContainer->pSkinInfo == nullptr) return;


#if SKINNED_MESH_TYPE == SKINNED_MESH_TYPE_DEVICE
	// ����̽��� �̿��� �ִ� ���� ����ġ ������ �׷��� ī�� ���� ���ο� ���ӵǱ� ������ �̸� �˻簡 �ʿ�
	D3DCAPS9 devCaps;
	GET_DEVICE_MANAGER()->getDirect3D()->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &devCaps);
	
	auto meshCont = (allocateHierarchy::meshContainer*)meshContainer;

	for (int i = 0; i < meshCont->vBoneCombinationList.size(); ++i)
	{
		int numBlends = 0;
		auto boneComb = meshCont->vBoneCombinationList[i];

		// ���� ����ġ ���� Ƚ�� Ž��
		for (int j = 0; j < meshCont->numBlends; ++j)
		{
			// �� ���� ������ ���� UINT_MAX�� �ƴ� ��� ���� ����ġ�� ������ �޴� ������ �ִٴ� ���� �ǹ�
			if (boneComb.BoneId[j] != UINT_MAX)
				numBlends = j;
		}
		
		// �׷��� ī�忡�� �����ϴ� �ִ� ���� ����ġ ���� Ƚ���� ������ ���
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
			// �ؽ��� ����
			int attributeID = boneComb.AttribId;
			MN_DEV->SetTexture(0, meshCont->vTextureList[attributeID]);
			MN_DEV->SetRenderState(D3DRS_VERTEXBLEND, numBlends);	// ���� ����ġ ���� Ȱ��ȭ(�����ϰ� �� ���� ��� ����)

			meshCont->pSkinndMesh->DrawSubset(i);
		}
	}
	// ���� ����ġ ���� ��Ȱ��ȭ
	MN_DEV->SetRenderState(D3DRS_VERTEXBLEND, 0);

#else
	auto meshCont = (allocateHierarchy::meshContainer*)meshContainer;
	for (int i = 0; i < meshCont->vBoneCombinationList.size(); ++i)
	{
		int numBlends = 0;
		auto boneComb = meshCont->vBoneCombinationList[i];
		
		// ���� ����ġ ���� Ƚ�� Ž��
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

	// ���� �� ����
	if (frame->pFrameSibling != nullptr)
		setupBone(frame->pFrameSibling);

	// �ڽ� �� ����
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
			auto boneName = meshCont->pSkinInfo->GetBoneName(i);	// �ش� ���� �̸��� ��ȯ
			auto bone = D3DXFrameFind(_rootBone, boneName);			// root ���� �̸��� �̿��� ���� Ž��
			
			meshCont->vBoneList.push_back((allocateHierarchy::boneFrame*)bone);
		}
	}
}

LPD3DXMESH skinnedMesh::createSkinnedMeshFromX(const string & filePath)
{
	/*
		std::bind ��ü�� ���� �� ���� �⺻������ �Լ� ȣ�� �� �Ѱ����� �Ű� ������ ���� ����ϴ°��� ��Ģ
		(��, �ش� ������� ������ std::bind ��ü�� �Լ� ȣ�� ��, �׻� ������ ���� �Ű� ������ �Ѱ���)

		�ݸ�, �Լ� ȣ�� �� �ٸ� ���� �Ű� ������ �ѱ�� ���ؼ� std::bind ��ü�� ���� �� ��
		std::placeholders �� �̿��Ͽ� ������ �Ű� ���� �ڸ��� ä����� ��
	*/
	allocateHierarchy::mParam aParam = {
		_basePath,
		std::bind(&skinnedMesh::createSkinnedMesh, this, std::placeholders::_1, std::placeholders::_2)
	};

	allocateHierarchy aHierarchy(aParam);

	LPD3DXANIMATIONCONTROLLER aniController = nullptr;

	// �޽� ����
	D3DXLoadMeshHierarchyFromXA(
		filePath.c_str(),
		D3DXMESH_MANAGED,
		MN_DEV,
		&aHierarchy,
		NULL,
		(LPD3DXFRAME*)&_rootBone,	// �ֻ��� ��
		&aniController);			// �ִϸ��̼��� �����ϱ� ���� ��Ʈ��
	
	// �ִϸ��̼� ��Ʈ�ѷ� ����
	_aniController = new animationController(aniController);

	// �� ����
	setupBone(_rootBone);

	/*
		�𵨸� ������ ������ ���� meshContainer�� N�� �̻��� �������� �� �ֱ� ������
		�ش� meshContainer�� ù��° ��ü�� ���� �޽� ������ ��ȯ
		(�Ϲ������� meshContainer�� ù��°�� �𵨸� ������ ��ü�� �ش�)
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

	// ��Ų�� �޽��� ��ȯ
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
			��Ű�� �ִϸ��̼��� ó���ϱ� ���ؼ� ���� ������ ���� ����ġ�� ��Ÿ����
			BLENDWEIGHT �ø�ƽ�� �ݵ�� ���ԵǾ�� ��
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

	// ����, ����, ������ ���� ���
	D3DXComputeNormals(pMesh, result->pAdjacency);
	D3DXComputeTangent(pMesh, 0, 0, 0, true, result->pAdjacency);

	// ��Ű�� ���� ����
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
