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
patternMesh::patternMesh(const mParam & a_rstParameters, ECharacterType characterType)
	:
	_param(a_rstParameters),
	_characterType(characterType)
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

void patternMesh::init(void)
{
	this->setBoneBoundBox();
	this->setBoneBoundSphere();
}

void patternMesh::update(void)
{
	renderObject::update();

	_isCull = false;
	this->updateBoneMatrix(_rootBone, getMatrixFinal());

	// �������� ��� handMatrix ������Ʈ
	if (_leftFingerNumber != 0 && _rightFingerNumber != 0)
	{
		if (_leftFingerNumber != -1)
		{
			_handMatrix[0] = _vMeshContainerList[0]->vBoneList[_leftFingerNumber]->combineMatrix;
		}
		else
		{
			findPart("Finger0", _leftFingerNumber);
			_handMatrix[0] = _vMeshContainerList[0]->vBoneList[_leftFingerNumber]->combineMatrix;
		}
		if (_rightFingerNumber != -1)
		{
			_handMatrix[1] = _vMeshContainerList[0]->vBoneList[_rightFingerNumber]->combineMatrix;
		}
		else
		{
			findPart("R_Hand", _rightFingerNumber);
			_handMatrix[1] = _vMeshContainerList[0]->vBoneList[_rightFingerNumber]->combineMatrix;
		}
		
	}
	if (_neckNumber != 0)
	{
		if (_neckNumber != -1)
		{
			_neckMatrix = _vMeshContainerList[0]->vBoneList[_neckNumber]->combineMatrix;
		}
		else
		{
			findPart("Neck", _neckNumber);
			_neckMatrix = _vMeshContainerList[0]->vBoneList[_neckNumber]->combineMatrix;
		}
	}

	// �ٿ�� ���Ǿ� ������Ʈ
	// {
	D3DXVec3TransformCoord(&_bSphere.center, &_bSphere.center, &getMatrixFinal());
	setBoundingSphere(_bSphere, _offset);
	// }

	// ���Ǿ� ����� ��ġ ������Ʈ
	for (int i = 0; i < _vBoneNameList.size(); ++i)
	{
		boundingSphere mSphere = _mbSphereSet.find(_vBoneNameList[i])->second.sphere;
		D3DXMATRIXA16 stMat = _mbBoxSet.find(_vBoneNameList[i])->second.matrix;
		D3DXMATRIXA16 stTrans;
		D3DXMatrixTranslation(&stTrans, mSphere.center.x, mSphere.center.y, mSphere.center.z);
		D3DXMATRIXA16 mWorld = stMat * stTrans;

		D3DXVECTOR3 stPos(0, 0, 0);
		D3DXVec3TransformCoord(&stPos, &stPos, &mWorld);
		_mbSphereSet.find(_vBoneNameList[i])->second.drawPosition = stPos;
	}

}

void patternMesh::findPart(const char * partName, int & partNumber)
{
	for (int i = 0; i < _vMeshContainerList[0]->vBoneList.size(); ++i)
	{
		std::string name = _vMeshContainerList[0]->vBoneList[i]->Name;
		if (name.find(partName) != string::npos)
		{
			partNumber = i;
			return;
		}
	}

	partNumber = 0;
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
}

void patternMesh::drawPost(void)
{
	renderObject::drawPost();

}

void patternMesh::drawpreMesh(ACInfo & acInfo)
{
	_aniControllerDigit->drawPre(acInfo);
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

	// �Ĺ��� ��Ʈ���� ����
	if (pstBone->Name != NULL)
	{
		if (_mBoneInfoList.find(pstBone->Name) != _mBoneInfoList.end())
		{
			_mBoneInfoList.find(pstBone->Name)->second.combineMatrix = pstBone->combineMatrix;

			setBoundingBoxMatrix(pstBone->Name, _mBoneInfoList.find(pstBone->Name)->second.combineMatrix);
		}
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

void patternMesh::setupBoneInfo(std::string name, const D3DXVECTOR3 & position, BYTE width, BYTE height, BYTE depth)
{
	switch (_characterType)
	{
	case ECharacterType::PLAYBLE:case ECharacterType::NORMAL_ZOMBIE:case ECharacterType::NONE:
	{
		STBoneInfo boneInfo;
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
		_mBoneInfoList.insert(unordered_map<string, STBoneInfo>::value_type(name, boneInfo));
		_vBoneNameList.push_back(name);

		STBoxSize boxSize;
		ZeroMemory(&boxSize, sizeof(boxSize));

		boxSize.width = width;
		boxSize.height = height;
		boxSize.depth = depth;

		_mBoxSizeList.insert(BOXSIZELIST::value_type(name, boxSize));
	}
	}
}

void patternMesh::setBoneBoundBox(void)
{
	switch (_characterType)
	{
	case ECharacterType::PLAYBLE:case ECharacterType::NORMAL_ZOMBIE:case ECharacterType::NONE:
	{
		for (int i = 0; i < _vBoneNameList.size(); ++i)
		{
			if (_mBoneInfoList.find(_vBoneNameList[i]) != _mBoneInfoList.end())
			{
				D3DXVec3TransformCoord(&_mBoneInfoList.find(_vBoneNameList[i])->second.position,
					&_mBoneInfoList.find(_vBoneNameList[i])->second.position,
					&_mBoneInfoList.find(_vBoneNameList[i])->second.combineMatrix);

				STBoxSize stBoxSize = _mBoxSizeList.find(_vBoneNameList[i])->second;

				BOUNDBOXSET boundSet;
				ZeroMemory(&boundSet, sizeof(boundSet));
				boundSet.box = gFunc::createBoundingBox(
					this->getPosition() + _mBoneInfoList.find(_vBoneNameList[i])->second.position,
					stBoxSize.width, stBoxSize.height, stBoxSize.depth);

				boundSet.matrix = _mBoneInfoList.find(_vBoneNameList[i])->second.combineMatrix;

				setBoundingBox(_vBoneNameList[i], boundSet);
			}
		}
		break;
	}
	}
}

void patternMesh::setBoneBoundSphere(void)
{
	switch (_characterType)
	{
	case ECharacterType::PLAYBLE:case ECharacterType::NORMAL_ZOMBIE:case ECharacterType::NONE:
	{
		for (int i = 0; i < _vBoneNameList.size(); ++i)
		{
			if (_mBoneInfoList.find(_vBoneNameList[i]) != _mBoneInfoList.end())
			{
				D3DXVec3TransformCoord(&_mBoneInfoList.find(_vBoneNameList[i])->second.position,
					&_mBoneInfoList.find(_vBoneNameList[i])->second.position,
					&_mBoneInfoList.find(_vBoneNameList[i])->second.combineMatrix);

				STBoxSize stBoxSize = _mBoxSizeList.find(_vBoneNameList[i])->second;
				BOUNDSPHERESET boundSet;
				ZeroMemory(&boundSet, sizeof(boundSet));
				D3DXMATRIXA16 stTrans;
				D3DXVECTOR3 stDrawPosition(0, 0, 0);
				D3DXMatrixTranslation(&stTrans, boundSet.sphere.center.x, boundSet.sphere.center.y, boundSet.sphere.center.z);
				D3DXVec3TransformCoord(&stDrawPosition, &stDrawPosition, &(boundSet.matrix * stTrans));

				boundSet.sphere = gFunc::createBoundingSphere(
					this->getPosition() + _mBoneInfoList.find(_vBoneNameList[i])->second.position,
					stBoxSize.width / 1.3);

				boundSet.matrix = _mBoneInfoList.find(_vBoneNameList[i])->second.combineMatrix;
				boundSet.drawPosition = stDrawPosition;

				setBoundingSphere(_vBoneNameList[i], boundSet);
			}
		}

		setBoundingSphere(gFunc::createBoundingSphere(D3DXVECTOR3(0.0f, 1.4f, 0.0f), 60),
			D3DXVECTOR3(0.0f, 1.4f, 0.0f));

		break;
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
