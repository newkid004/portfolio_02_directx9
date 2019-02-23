#include "maptool_data_catalog.h"

#include "managerList.h"
#include "gFunc.h"

#include "staticMesh.h"
#include "skinnedMesh.h"
#include "nodeMesh.h"
#include "triggerMesh.h"
#include "spawner.h"

#include "triggerBase.h"
#include "triggerFactory.h"

maptool_data_catalog::OBJ::PROP::~PROP()
{
	SAFE_DELETE(_object);
}

void maptool_data_catalog::create(OBJ::PROP ** out, void * param)
{
	OBJ::PROP* result = new OBJ::PROP();
	result->_object = new staticMesh(*(staticMesh::mParam*)param);

	*out = result;
}

void maptool_data_catalog::create(OBJ::BUMP ** out, void * param)
{
	OBJ::BUMP* result = new OBJ::BUMP();
	result->_object = new staticMesh(*(staticMesh::mParam*)param);

	*out = result;
}

void maptool_data_catalog::create(OBJ::CHAR ** out, void * param)
{
	OBJ::CHAR* result = new OBJ::CHAR();
	result->_object = new skinnedMesh(*(skinnedMesh::mParam*)param);

	*out = result;
}

void maptool_data_catalog::create(OBJ::NODE ** out, void * param)
{
	OBJ::NODE* result = new OBJ::NODE();
	result->_object = new nodeMesh(*(nodeMesh::mParam*)param);

	*out = result;
}

void maptool_data_catalog::create(OBJ::TRIGGER ** out, void * param)
{
	OBJ::TRIGGER* result = new OBJ::TRIGGER();
	result->_object = new triggerMesh(*(triggerMesh::mParam*)param);

	*out = result;
}

void maptool_data_catalog::create(OBJ::SPAWNER ** out, void * param)
{
	OBJ::SPAWNER* result = new OBJ::SPAWNER();
	result->_object = new spawner(*(spawner::mParam*)param);

	*out = result;
}

// ----- duplicate ----- //
void maptool_data_catalog::duplicate(staticMesh ** outObject, OBJ::PROP * targetObject)
{
	staticMesh* obj = (staticMesh*)targetObject->_object;
	staticMesh* result = new staticMesh(obj->getMakeParam());

	applyObject(result, obj);
	*outObject = result;
}

void maptool_data_catalog::duplicate(staticMesh ** outObject, OBJ::BUMP * targetObject)
{
	staticMesh* obj = (staticMesh*)targetObject->_object;
	staticMesh* result = new staticMesh(obj->getMakeParam());

	applyObject(result, obj);
	*outObject = result;
}

void maptool_data_catalog::duplicate(skinnedMesh ** outObject, OBJ::CHAR * targetObject)
{
	skinnedMesh* obj = (skinnedMesh*)targetObject->_object;
	skinnedMesh* result = new skinnedMesh(obj->getMakeParam());

	applyObject(result, obj);
	*outObject = result;
}

void maptool_data_catalog::duplicate(nodeMesh ** outObject, OBJ::NODE * targetObject)
{
	nodeMesh* obj = (nodeMesh*)targetObject->_object;
	nodeMesh* result = new nodeMesh(obj->getMakeParam());

	applyObject(result, obj);
	*outObject = result;
}

void maptool_data_catalog::duplicate(triggerMesh ** outObject, OBJ::TRIGGER * targetObject)
{
	triggerMesh* obj = (triggerMesh*)targetObject->_object;
	triggerMesh* result = new triggerMesh(obj->getMakeParam());

	applyObject(result, obj);
	result->refBind() = triggerFactory::createTrigger2type(targetObject->_triggerType, result);

	*outObject = result;
}

void maptool_data_catalog::duplicate(spawner ** outObject, OBJ::SPAWNER * targetObject)
{
	spawner* obj = (spawner*)targetObject->_object;
	spawner* result = new spawner(obj->getMakeParam());

	applyObject(result, obj);
	*outObject = result;
}

void maptool_data_catalog::applyObject(renderObject * target, renderObject * own)
{
	target->setScale(own->getScale());

	target->setDirectionForward(own->getDirectForward());
	target->setDirectionUp(own->getDirectUp());
	target->setDirectionRight(own->getDirectRight());

	target->setMatrixOffset(own->getOffsetMatrix());
}

void maptool_data_catalog::applyObject(nodeMesh * target, nodeMesh * own)
{
	applyObject((renderObject*)target, (renderObject*)own);

	target->setNodeColor(own->getNodeColor());
	target->setPlaneRadius(own->getPlaneRadius());
	target->getMeshSet()->vTextureList[0] = own->getMeshSet()->vTextureList[0];
}

void maptool_data_catalog::applyObject(triggerMesh * target, triggerMesh * own)
{
	applyObject((renderObject*)target, (renderObject*)own);
}

void maptool_data_catalog::applyObject(spawner * target, spawner * own)
{
	applyObject((nodeMesh*)target, (nodeMesh*)own);
}
