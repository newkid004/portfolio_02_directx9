#include "patternMeshDup.h"
#include "patternMesh.h"

patternMeshDup::patternMeshDup(patternMesh * duplicateTarget)
	:_bindPatternMesh(duplicateTarget)
{
}

patternMeshDup::~patternMeshDup(void)
{
}

void patternMeshDup::update(void)
{
	renderObject::update();
}

void patternMeshDup::drawPre(void)
{
	_bindPatternMesh->setPosition(_position);
	_bindPatternMesh->setDirectionForward(_directionForward);
	_bindPatternMesh->setDirectionRight(-_directionRight);
	_bindPatternMesh->setDirectionUp(-_directionUp);
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
	_finalHandMatrix[0] = _bindPatternMesh->getHandMatrix(0);
	_finalHandMatrix[1] = _bindPatternMesh->getHandMatrix(1);
	_finalNeckMatrix = _bindPatternMesh->getNeckMatrix();
}
