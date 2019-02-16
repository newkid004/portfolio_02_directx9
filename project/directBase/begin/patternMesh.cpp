#include "patternMesh.h"
#include "staticMesh.h"
#include "camera.h"
#include "direct3dApplication.h"
#include "gFunc.h"
#include "managerList.h"
#include "animationControllerDigit.h"

#include "lightBase.h"

#include "sceneBase.h"

using namespace std;
patternMesh::patternMesh(const mParam & a_rstParameters)
	:
	_param(a_rstParameters)
{
	if (a_rstParameters.filePath.rfind("/") != std::string::npos) {
		_basePath = a_rstParameters.filePath.substr(0,
			a_rstParameters.filePath.rfind("/") + 1);
	}

	_effect = MN_SRC->getEffect(a_rstParameters.effectFilePath);
	_mesh = this->createSkinnedMeshFromX(a_rstParameters.filePath);
}

patternMesh::~patternMesh(void)
{
	SAFE_DELETE(_aniControllerDigit);
}

void patternMesh::update(void)
{
	renderObject::update();
	
	_isCull = false;
	this->updateBoneMatrix(_rootBone, getMatrixFinal());

	if (_weapon != nullptr)
	{
		D3DXMATRIXA16 stWeaponMatrix;
		D3DXMATRIXA16 stRotationMatrix;
		D3DXMATRIXA16 stTranslation;
		if (_leftFingerNumber != -1)
		{
			stWeaponMatrix = _vMeshContainerList[0]->vBoneList[_leftFingerNumber]->combineMatrix;
			_vHandMatrix[0] = stWeaponMatrix;
		}
		else
		{
			_leftFingerNumber = findFinger(true);
			stWeaponMatrix = _vMeshContainerList[0]->vBoneList[_leftFingerNumber]->combineMatrix;
			_vHandMatrix[0] = stWeaponMatrix;
		}
		if (_rightFingerNumber != -1)
		{
			stWeaponMatrix = _vMeshContainerList[0]->vBoneList[_rightFingerNumber]->combineMatrix;
			_vHandMatrix[1] = stWeaponMatrix;
		}
		else
		{
			_rightFingerNumber = findFinger(false);
			stWeaponMatrix = _vMeshContainerList[0]->vBoneList[_rightFingerNumber]->combineMatrix;
			_vHandMatrix[1] = stWeaponMatrix;
		}
		
		/*
		������ ����

		Rifle
		D3DXMatrixRotationYawPitchRoll(&stRotationMatrix,
			D3DXToRadian(90.0f), D3DXToRadian(175.0f), D3DXToRadian(-15.0f));
		D3DXMatrixTranslation(&stTranslation, 0.0f, 0.0f, -1.0f);

		SHOTGUN
		D3DXMatrixRotationYawPitchRoll(&stRotationMatrix,
			D3DXToRadian(70.0f), D3DXToRadian(190.0f), D3DXToRadian(-10.0f));
		D3DXMatrixTranslation(&stTranslation, 1.5f, 0.5f, -2.5f);
									//���//������ , ������*/


		/*
		�޼� ���� 
		Rilfe
		D3DXMatrixRotationYawPitchRoll(&stRotationMatrix,
			D3DXToRadian(70.0f), D3DXToRadian(205.0f), D3DXToRadian(180.0f));
		D3DXMatrixTranslation(&stTranslation, -15.0f, 3.0f, -8.0f);
		
		ShotGun
		
		D3DXMatrixRotationYawPitchRoll(&stRotationMatrix,
			D3DXToRadian(60.0f), D3DXToRadian(195.0f), D3DXToRadian(160.0f));
		D3DXMatrixTranslation(&stTranslation, -19.0f, 3.0f, -14.0f);
		
		healkit
		D3DXMatrixRotationYawPitchRoll(&stRotationMatrix,
			D3DXToRadian(0.0f), D3DXToRadian(0.0f), D3DXToRadian(0.0f));
		D3DXMatrixTranslation(&stTranslation, 0.0f, 0.0f, 0.0f);
		*/

		//_IsleftHand = false;
		//if (_IsleftHand)
		{
			D3DXMatrixRotationYawPitchRoll(&stRotationMatrix,
				D3DXToRadian(60.0f), D3DXToRadian(195.0f), D3DXToRadian(160.0f));
			D3DXMatrixTranslation(&stTranslation, -19.0f, 3.0f, -14.0f);
		}
		//else
		{
			D3DXMatrixRotationYawPitchRoll(&stRotationMatrix,
				D3DXToRadian(70.0f), D3DXToRadian(190.0f), D3DXToRadian(-10.0f));
			D3DXMatrixTranslation(&stTranslation, 1.5f, 0.5f, -2.5f);
		}

		stWeaponMatrix = stRotationMatrix * stTranslation * stWeaponMatrix;
		_weapon->update();
		_weapon->getIsCull() = _isCull;
		(*_weapon->getMatrixWorldPoint()) = (*_weapon->getMatrixWorldPoint())* stWeaponMatrix;
	}
}

int patternMesh::findFinger(bool isLeft)
{
	
	for (int i = 0; i < _vMeshContainerList[0]->vBoneList.size(); ++i)
	{
		std::string name = _vMeshContainerList[0]->vBoneList[i]->Name;
		if (isLeft)
		{
			if (name.find("Finger0") != string::npos)
			{
				return i;
			}
		}
		else
		{
			if (name.find("R_Hand") != string::npos)
			{
				return i;
			}
		}
	}
	return 0;
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

	this->drawBone(_rootBone);
	if (_weapon != nullptr)
	{
		_weapon->draw();
	}
}

void patternMesh::drawPost(void)
{
	renderObject::drawPost();

}

void patternMesh::drawpreMesh(ACInfo & acInfo)
{
	_aniControllerDigit->drawPre(acInfo);
}

void patternMesh::setWeapon(staticMesh * weapon)
{
	_weapon = weapon;
}

void patternMesh::updateBoneMatrix(LPD3DXFRAME a_pstFrame, const D3DXMATRIXA16 & a_rstMatrix)
{
	auto pstBone = (allocateHierarchy::boneFrame *)a_pstFrame;
	pstBone->combineMatrix = pstBone->TransformationMatrix * a_rstMatrix;

	// ���� �� ������ ���� ���
	if (pstBone->pFrameSibling != nullptr) {
		this->updateBoneMatrix(pstBone->pFrameSibling, a_rstMatrix);
	}

	// �ڽ� �� ������ ���� ���
	if (pstBone->pFrameFirstChild != nullptr) {
		this->updateBoneMatrix(pstBone->pFrameFirstChild, pstBone->combineMatrix);
	}
}

void patternMesh::drawBone(LPD3DXFRAME a_pstFrame)
{
	auto pstMeshContainer = a_pstFrame->pMeshContainer;

	while (pstMeshContainer != nullptr) {
		this->drawMeshContainer(a_pstFrame, pstMeshContainer);
		pstMeshContainer = (LPD3DXMESHCONTAINER)pstMeshContainer->pNextMeshContainer;
	}

	// ���� �� ������ ���� ���
	if (a_pstFrame->pFrameSibling != nullptr) {
		this->drawBone(a_pstFrame->pFrameSibling);
	}

	// �ڽ� �� ������ ���� ���
	if (a_pstFrame->pFrameFirstChild != nullptr) {
		this->drawBone(a_pstFrame->pFrameFirstChild);
	}
}

void patternMesh::drawMeshContainer(LPD3DXFRAME a_pstFrame, LPD3DXMESHCONTAINER a_pstMeshContainer)
{
	if (a_pstMeshContainer->pSkinInfo != nullptr) {
		auto pstMeshContainer = (allocateHierarchy::meshContainer *)a_pstMeshContainer;

		for (int i = 0; i < pstMeshContainer->vBoneCombinationList.size(); ++i) {
			int nNumBlends = 0;
			auto stBoneCombination = pstMeshContainer->vBoneCombinationList[i];

			// ���� ����ġ ���� Ƚ���� Ž���Ѵ�
			for (int j = 0; j < pstMeshContainer->numBlends; ++j) {
				if (stBoneCombination.BoneId[j] != UINT_MAX) {
					nNumBlends = j;
				}
			}

			// ���� ����� �����Ѵ�
			// {
			D3DXMATRIXA16 astWorldMatrices[4];
			int nSize = sizeof(astWorldMatrices) / sizeof(astWorldMatrices[0]);

			for (int j = 0; j < nSize; ++j) {
				D3DXMatrixIdentity(astWorldMatrices + j);
			}
			// }

			for (int j = 0; j < pstMeshContainer->numBlends; ++j) {
				int nBoneID = stBoneCombination.BoneId[j];

				if (nBoneID != UINT_MAX) {
					auto pstBone = pstMeshContainer->vBoneList[nBoneID];
					D3DXMATRIXA16 stBoneMatrix = pstMeshContainer->vBoneMatrixList[nBoneID];

					astWorldMatrices[j] = stBoneMatrix * pstBone->combineMatrix;
				}
			}

			_effect->SetInt("_numBlend", nNumBlends);
			_effect->SetMatrixArray("_mWorld", astWorldMatrices, 4);

			int attributeID = stBoneCombination.AttribId;
			_effect->SetTexture("_texture", pstMeshContainer->vTextureList[attributeID]);
			if (pstMeshContainer->vNormalTextureList[attributeID] != nullptr)
			{
				_effect->SetTexture("_normalTexture", pstMeshContainer->vNormalTextureList[attributeID]);
			}

			gFunc::runEffectLoop(_effect, "myTechnique", [&](int passNum)->void {
				pstMeshContainer->pSkinndMesh->DrawSubset(i);
			});
		}
	}
}

void patternMesh::setupBone(LPD3DXFRAME a_pstFrame)
{
	if (a_pstFrame->pMeshContainer != nullptr) {
		this->setupBoneOnMeshContainer(a_pstFrame, a_pstFrame->pMeshContainer);
	}

	// ���� �� ������ ���� ���
	if (a_pstFrame->pFrameSibling != nullptr) {
		this->setupBone(a_pstFrame->pFrameSibling);
	}

	// �ڽ� �� ������ ���� ���
	if (a_pstFrame->pFrameFirstChild != nullptr) {
		this->setupBone(a_pstFrame->pFrameFirstChild);
	}
}

void patternMesh::setupBoneOnMeshContainer(LPD3DXFRAME a_pstFrame, LPD3DXMESHCONTAINER a_pstMeshContainer)
{
	auto pstMeshContainer = (allocateHierarchy::meshContainer *)a_pstMeshContainer;

	if (pstMeshContainer->pSkinInfo != nullptr) {
		int nNumBones = pstMeshContainer->pSkinInfo->GetNumBones();

		for (int i = 0; i < nNumBones; ++i) {
			/*
			GetBoneName �Լ��� ���� �ĺ��ڸ� �̿��ؼ� �ش� ���� �̸���
			��ȯ�ϴ� ������ �Ѵ�.
			*/
			auto pszBoneName = pstMeshContainer->pSkinInfo->GetBoneName(i);

			/*
			D3DXFrameFind �Լ��� ��Ʈ ���� ���� �̸��� �̿��ؼ� Ư�� ����
			Ž���ϴ� ������ �Ѵ�.
			*/
			auto pstBone = D3DXFrameFind(_rootBone, pszBoneName);
			pstMeshContainer->vBoneList.push_back((allocateHierarchy::boneFrame *)pstBone);
		}
	}
}

LPD3DXMESH patternMesh::createSkinnedMeshFromX(const std::string & a_rFilepath)
{
	/*
	std::bind ��ü�� ���� �� ���� �⺻������ �Լ� ȣ�� �� �Ѱ����� �Ű� ������ ����
	����ϴ� ���� ��Ģ�̴�. (��, �ش� ������� ���� �� std::bind ��ü�� �Լ� ȣ�� ��
	�׻� ������ ���� �Ű� ������ �Ѱ�����.)

	�ݸ�, �Լ� ȣ�� �� �ٸ� ���� �Ű� ������ �ѱ�� ���ؼ��� std::bind ��ü�� ���� �� ��
	std::placehlders �� �̿��ؼ� �Ű� ������ �ڸ��� �������� ä���־���Ѵ�.
	*/
	allocateHierarchy::mParam stParameters = {
		_basePath,
		std::bind(&patternMesh::createSkinnedMesh, this, std::placeholders::_1, std::placeholders::_2)
	};

	allocateHierarchy oAllocateHierarchy(stParameters);
	LPD3DXANIMATIONCONTROLLER pAnimationController = nullptr;

	// �޽ø� �����Ѵ�
	D3DXLoadMeshHierarchyFromXA(a_rFilepath.c_str(),
		D3DXMESH_MANAGED,
		MN_DEV,
		&oAllocateHierarchy,
		NULL,
		(LPD3DXFRAME *)&_rootBone,			// ���� �����ϴ� �� �߿� �ֻ��� ��
		&pAnimationController);					// �ִϸ��̼��� �����ϱ� ���� ��Ʈ�ѷ�

												// ���� �����Ѵ�
	this->setupBone(_rootBone);

	// �ִϸ��̼� ��Ʈ�ѷ��� �����Ѵ�
	_aniControllerDigit = new animationControllerDigit(pAnimationController);

	/*
	�𵨸� ������ ������ ���� MeshContainer �� N �� �̻��� ���� �� �� �ֱ� ������
	�ش� MeshContainer �߿��� ���� ù��° ��ü�� ���ϰ� �ִ� �޽� ������ ��ȯ�Ѵ�.

	(��, �Ϲ������� ���� ó���� �ش��ϴ� MeshContainer �� �𵨸� ������ ��ü��
	�ش��Ѵ�.)
	*/
	return _vMeshContainerList.front()->pSkinndMesh;
}

LPD3DXMESH patternMesh::createSkinnedMesh(LPD3DXMESHCONTAINER a_pstMeshContainer, int a_nMeshContainerNumber)
{
	auto pstMeshContainer = (allocateHierarchy::meshContainer *)a_pstMeshContainer;

	DWORD nNumBlends = 0;
	DWORD nNumBoneCombinations = 0;

	LPD3DXMESH pMesh = nullptr;
	LPD3DXBUFFER pBoneCombinationBuffer = nullptr;

	// ��Ų�� �޽÷� ��ȯ�Ѵ�
	pstMeshContainer->pSkinInfo->ConvertToBlendedMesh(pstMeshContainer->MeshData.pMesh,
		pstMeshContainer->MeshData.pMesh->GetOptions() | D3DXMESHOPT_VERTEXCACHE,
		pstMeshContainer->pAdjacency,
		pstMeshContainer->pAdjacency,
		NULL,
		NULL,
		&nNumBlends,
		&nNumBoneCombinations,
		&pBoneCombinationBuffer,
		&pMesh);

	// ���� ������ �����Ѵ�
	// {
	D3DVERTEXELEMENT9 astElements[] = {
		0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0,
		0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0,
		0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0,
		0, 36, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0,
		0, 48, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0,

		/*
		��Ű�� �ִϸ��̼��� ó���ϱ� ���ؼ��� ���� ������ �ݵ�� ���� ����ġ ������
		�ش��ϴ� BLENDWEIGHT �ø�ƽ�� �ݵ�� ���ԵǾ��־���Ѵ�.
		*/
		0, 56, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0,
		D3DDECL_END()
	};

	auto pOriginMesh = pMesh;

	// �纻 �޽ø� �����Ѵ�
	pOriginMesh->CloneMesh(pOriginMesh->GetOptions(),
		astElements,
		MN_DEV,
		&pMesh);

	// ���� ������ ����Ѵ�
	D3DXComputeNormals(pMesh, pstMeshContainer->pAdjacency);

	// ����, ������ ������ ����Ѵ�
	D3DXComputeTangent(pMesh, 0, 0, 0, TRUE, pstMeshContainer->pAdjacency);
	// }

	// ��Ű�� ������ �����Ѵ�
	// {
	pstMeshContainer->numBlends = nNumBlends;
	auto pstBoneCombinations = (LPD3DXBONECOMBINATION)pBoneCombinationBuffer->GetBufferPointer();

	// �� ���� ������ �����Ѵ�
	for (int i = 0; i < nNumBoneCombinations; ++i) {
		D3DXBONECOMBINATION stBoneCombination = pstBoneCombinations[i];

		auto stCopiedBoneCombination = stBoneCombination;
		stCopiedBoneCombination.BoneId = (DWORD *)malloc(sizeof(DWORD) * nNumBlends);

		CopyMemory(stCopiedBoneCombination.BoneId, stBoneCombination.BoneId, sizeof(DWORD) * nNumBlends);
		pstMeshContainer->vBoneCombinationList.push_back(stCopiedBoneCombination);
	}
	// }

	SAFE_RELEASE(pOriginMesh);
	SAFE_RELEASE(pBoneCombinationBuffer);

	_vMeshContainerList.push_back(pstMeshContainer);
	return pMesh;
}
