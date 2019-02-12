#include "patternMesh.h"

#include "camera.h"
#include "direct3dApplication.h"
#include "gFunc.h"
#include "managerList.h"
#include "animationControllerDigit.h"

#include "lightBase.h"

#include "sceneBase.h"

using namespace std;

patternMesh::patternMesh(const mParam & param) :
	_param(param)
{
	if (param.filePath.rfind("/") != string::npos)
		_basePath = param.filePath.substr(0, param.filePath.rfind("/") + 1);

	_effect = MN_SRC->getEffect(param.effectFilePath);
	_mesh = createSkinnedMeshFromX(param.filePath);


	for (int i = 0; i < _vMeshContainerList.size(); ++i)
	{
		setBoundingBox(gFunc::createBoundingBox(_vMeshContainerList[i]->pSkinndMesh));
		setBoundingSphere(gFunc::createBoundingSphere(_vMeshContainerList[i]->pSkinndMesh));
	}

}

patternMesh::~patternMesh()
{
	SAFE_DELETE(_aniControllerDigit);
}

void patternMesh::update(void)
{
	renderObject::update();

	updateBoneMatrix(_rootBone, getMatrixFinal());
}

void patternMesh::drawPre(void)
{
	renderObject::drawPre();

	_effect->SetMatrix("_mView", &GET_CAMERA()->getMatrixView());
	_effect->SetMatrix("_mProjection", &GET_CAMERA()->getMatrixProjection());
	_effect->SetMatrix("_mViewProjection", &GET_CAMERA()->getMatrixViewProjection());

	D3DXVECTOR4 viewPosition(GET_CAMERA()->getPosition(), 1.0f);
	_effect->SetVector("_viewPosition", &viewPosition);

	D3DXVECTOR4 lightDirection(GET_LIGHT()->getDirectForward(), 0.0f);
	D3DXVec4Normalize(&lightDirection, &lightDirection);
	_effect->SetVector("_lightDirection", &lightDirection);

}

void patternMesh::drawDo(void)
{
	renderObject::drawDo();

	drawBone(_rootBone);
}

void patternMesh::drawPost(void)
{
	renderObject::drawPost();
}

void patternMesh::updateBoneMatrix(void)
{
	updateBoneMatrix(_rootBone, getMatrixFinal());
}

void patternMesh::drawpreMesh(ACInfo & acInfo)
{
	_aniControllerDigit->drawPre(acInfo);
}

void patternMesh::updateBoneMatrix(LPD3DXFRAME frame, const D3DXMATRIXA16 & mUpdate)
{
	auto bone = (allocateHierarchy::boneFrame*)frame;

	bone->combineMatrix = bone->TransformationMatrix * mUpdate;

	// ���� �� ����
	if (bone->pFrameSibling != nullptr)		updateBoneMatrix(bone->pFrameSibling, mUpdate);
	if (bone->pFrameFirstChild != nullptr)	updateBoneMatrix(bone->pFrameFirstChild, bone->combineMatrix);
}

void patternMesh::drawBone(LPD3DXFRAME frame)
{
	auto meshCont = frame->pMeshContainer;

	while (meshCont != nullptr)
	{
		drawMeshContainer(frame, meshCont);
		//drawBox();
		meshCont = meshCont->pNextMeshContainer;
	}

	// ���� �� ������ ���� ���
	if (frame->pFrameSibling != nullptr)
		drawBone(frame->pFrameSibling);

	// �ڽ� �� ������ ���� ���
	if (frame->pFrameFirstChild != nullptr)
		drawBone(frame->pFrameFirstChild);
}

void patternMesh::drawMeshContainer(LPD3DXFRAME frame, LPD3DXMESHCONTAINER meshContainer)
{
	if (meshContainer->pSkinInfo == nullptr) return;

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
}

void patternMesh::drawBox(void)
{
}

void patternMesh::setupBone(LPD3DXFRAME frame)
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

void patternMesh::setupBoneOnMeshContainer(LPD3DXFRAME frame, LPD3DXMESHCONTAINER meshContainer)
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

LPD3DXMESH patternMesh::createSkinnedMeshFromX(const string & filePath)
{
	allocateHierarchy::mParam aParam = {
		_basePath,
		std::bind(&patternMesh::createSkinnedMesh, this, std::placeholders::_1, std::placeholders::_2)
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
	_aniControllerDigit = new animationControllerDigit(aniController);

	// �� ����
	setupBone(_rootBone);

	/*
	�𵨸� ������ ������ ���� meshContainer�� N�� �̻��� �������� �� �ֱ� ������
	�ش� meshContainer�� ù��° ��ü�� ���� �޽� ������ ��ȯ
	(�Ϲ������� meshContainer�� ù��°�� �𵨸� ������ ��ü�� �ش�)
	*/

	return _vMeshContainerList.front()->pSkinndMesh;
}

LPD3DXMESH patternMesh::createSkinnedMesh(LPD3DXMESHCONTAINER meshContainer, int meshContainerNumber)
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

	// ����, ����, ������ ���� ���
	D3DXComputeNormals(pMesh, result->pAdjacency);
	D3DXComputeTangent(pMesh, 0, 0, 0, true, result->pAdjacency);

	// ��Ű�� ���� ����
	result->numBlends = numBlends;
	auto boneCombinations = (LPD3DXBONECOMBINATION)bufBoneCombinations->GetBufferPointer();

	for (int i = 0; i < numBoneCombinations; ++i)
	{
		D3DXBONECOMBINATION & boneComb = boneCombinations[i];

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
