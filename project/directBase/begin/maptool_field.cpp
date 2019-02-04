#include "maptool_field.h"

#include "managerList.h"
#include "gFunc.h"

#include "sceneBase.h"
#include "camera.h"

#include "terrain.h"
#include "quadTree_Frustum.h"

maptool_field::maptool_field(terrain* inTerrain)
{
	_fieldSet.field = inTerrain;

	if (_fieldSet.field)
		_fieldSet.qTree = new quadTree_Frustum(inTerrain->getSizeMap().cx, inTerrain->getSizeMap().cy);
	else
		_fieldSet.qTree = new quadTree_Frustum(256, 256);
}

maptool_field::~maptool_field()
{
	SAFE_DELETE(_fieldSet.field);
	SAFE_DELETE(_fieldSet.qTree);

	for (auto i : _fieldSet.objList)
		SAFE_DELETE(i);

	for (auto i : _fieldSet.dataList)
		SAFE_DELETE(i);
}

void maptool_field::update(void)
{
	for (auto i : _fieldSet.objList)
		i->update();
}

void maptool_field::draw(void)
{
	for (auto i : _fieldSet.objList)
	{
		if (auto rObject = dynamic_cast<renderObject*>(i))
			rObject->draw();
	}
}
