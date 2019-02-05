#include "maptool_data_catalog.h"

#include "managerList.h"
#include "gFunc.h"

#include "staticMesh.h"
#include "skinnedMesh.h"

maptool_data_catalog::OBJ::PROP::~PROP()
{
	SAFE_DELETE(_object);
}

void maptool_data_catalog::createProp(OBJ::PROP ** out, void * param)
{
	OBJ::PROP* result = new OBJ::PROP();
	result->_object = new staticMesh(*(staticMesh::mParam*)param);

	*out = result;
}

void maptool_data_catalog::createChar(OBJ::CHAR ** out, void * param)
{
	OBJ::CHAR* result = new OBJ::CHAR();
	result->_object = new skinnedMesh(*(skinnedMesh::mParam*)param);

	*out = result;
}

// ----- duplicate ----- //
void maptool_data_catalog::duplicate(OBJ::BASE ** outObject, OBJ::BASE * targetObject)
{
	OBJ::BASE* result = new OBJ::BASE();
	result->_standImage = targetObject->_standImage;

	*outObject = result;
}

void maptool_data_catalog::duplicate(OBJ::PROP ** outObject, OBJ::PROP * targetObject)
{
	OBJ::PROP* result = new OBJ::PROP();

	result->_standImage = targetObject->_standImage;
	result->_object = new staticMesh(((staticMesh*)targetObject->_object)->getMakeParam());

	*outObject = result;
}

void maptool_data_catalog::duplicate(OBJ::CHAR ** outObject, OBJ::CHAR * targetObject)
{
	OBJ::CHAR* result = new OBJ::CHAR();

	result->_standImage = targetObject->_standImage;
	result->_object = new skinnedMesh(((skinnedMesh*)targetObject->_object)->getMakeParam());

	*outObject = result;
}

void maptool_data_catalog::duplicate(OBJ::EVENT ** outObject, OBJ::EVENT * targetObject)
{
	OBJ::EVENT* result = new OBJ::EVENT();
	result->_standImage = targetObject->_standImage;

	*outObject = result;
}
