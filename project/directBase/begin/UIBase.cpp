#include "UIBase.h"

UIBase::UIBase() :
	_isVisible(true),
	_diffuseColor(COLOR_WHITE(255))
{
}

UIBase::~UIBase()
{
}

void UIBase::drawUI(void)
{
	if (_isVisible)
		drawDoUI();

	for (auto child : _vChildren)
	{
		auto rObject = dynamic_cast<UIBase*>(child);

		if (rObject != nullptr)
			rObject->drawUI();
	}
}