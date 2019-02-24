#include "patternMeshDup.h"
#include "patternMesh.h"
#include "managerList.h"

patternMeshDup::patternMeshDup(patternMesh * duplicateTarget)
	:_bindPatternMesh(duplicateTarget)
{
	ZeroMemory(&_controlInfo, sizeof(_controlInfo));

	// 충돌범위 복사
	_bBox = _bindPatternMesh->getBoundingBox();
	_bSphere = _bindPatternMesh->getBoundingSphere();
	_mbSphereSet = _bindPatternMesh->getBoundingSphereSetList();
}

patternMeshDup::~patternMeshDup(void)
{
}

void patternMeshDup::update(void)
{
	renderObject::update();

	_isCull = false;
}

void patternMeshDup::drawPre(void)
{
	_bindPatternMesh->drawpreMesh(_controlInfo);
	if (_bindPatternMesh->getOriginType() == patternMesh::type::survivor)
	{
		_bindPatternMesh->setDirectionForward(_directionForward);
		_bindPatternMesh->setDirectionRight(-_directionRight);
		_bindPatternMesh->setDirectionUp(-_directionUp);
	}
	else if (_bindPatternMesh->getOriginType() == patternMesh::type::male_zombie
		||_bindPatternMesh->getOriginType() == patternMesh::type::feMale_zombie)
	{
		_bindPatternMesh->setDirectionForward(_directionUp);
		_bindPatternMesh->setDirectionRight(_directionRight);
		_bindPatternMesh->setDirectionUp(_directionForward);
	}
	_bindPatternMesh->setPosition(_position);
	_bindPatternMesh->update();
	_bindPatternMesh->getIsCull() = false;
}

void patternMeshDup::drawDo(void)
{
	_bindPatternMesh->draw();

}

void patternMeshDup::drawPost(void)
{
	calcurateHandMatrix();
	calcurateBoundSphereMatrix();

}

void patternMeshDup::calcurateHandMatrix(void)
{
	_finalHandMatrix[0] =  _bindPatternMesh->getHandMatrix(0);
	_finalHandMatrix[1] = _bindPatternMesh->getHandMatrix(1);
	_finalNeckMatrix =  _bindPatternMesh->getNeckMatrix();
}

void patternMeshDup::calcurateBoundSphereMatrix(void)
{
	patternMesh::BONEINFOLIST _mBoneInfoList;
	_mBoneInfoList = _bindPatternMesh->getBoneInfoList();
	_bSphere = _bindPatternMesh->getBoundingSphere();
	_offset = _bindPatternMesh->getBoundingSphereOffset();
	_mbSphereSet.clear();
	for (auto rValue : _bindPatternMesh->getBoundingSphereSetList())
	{
		_mbSphereSet.insert(rValue);
	}

	BOUNDSPHEREMATRIXSET::iterator iter;
	for (iter = _mbSphereSet.begin(); iter != _mbSphereSet.end(); ++iter)
	{
		//iter->second.matrix = _mBoneInfoList.find(iter->first)->second.matrix * _bindPatternMesh->getMatrixFinal();
		iter->second.drawPosition = D3DXVECTOR3(0, 0, 0);
		D3DXVec3TransformCoord(&iter->second.drawPosition, &iter->second.drawPosition, &_mBoneInfoList.find(iter->first)->second.combineMatrix);
	}
	_bSphere.center = D3DXVECTOR3(0, 0, 0);
	D3DXVec3TransformCoord(&_bSphere.center, &_bSphere.center, &_bindPatternMesh->getMatrixFinal());


}
