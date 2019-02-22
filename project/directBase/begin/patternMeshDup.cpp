#include "patternMeshDup.h"
#include "patternMesh.h"

patternMeshDup::patternMeshDup(patternMesh * duplicateTarget)
	:_bindPatternMesh(duplicateTarget)
{
	ZeroMemory(&_controlInfo, sizeof(_controlInfo));

	// 충돌범위 복사
	_bBox = _bindPatternMesh->getBoundingBox();
	_bSphere = _bindPatternMesh->getBoundingSphere();
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
	_bindPatternMesh->drawpreMesh(_controlInfo);
}

void patternMeshDup::drawDo(void)
{
	_bindPatternMesh->draw();
}

void patternMeshDup::drawPost(void)
{
	calcurateHandMatrix();
}

void patternMeshDup::calcurateHandMatrix(void)
{
	_finalHandMatrix[0] =  _bindPatternMesh->getHandMatrix(0);
	_finalHandMatrix[1] = _bindPatternMesh->getHandMatrix(1);
	_finalNeckMatrix =  _bindPatternMesh->getNeckMatrix();
}
