#include "direct3dApplication.h"
#include "renderObject.h"
#include "managerList.h"
#include "gFunc.h"
#include "camera.h"
#include "debugGizmo.h"

renderObject::renderObject() :
	_isVisible(true)
{
}

renderObject::~renderObject()
{
}

void renderObject::draw(void)
{
	if (_isVisible)
	{
		drawPre();

		drawDo();

		drawPost();

	}

	for (auto child : _vChildren)
	{
		auto rObject = dynamic_cast<renderObject*>(child);

		if (rObject != nullptr)
			rObject->draw();
	}
}