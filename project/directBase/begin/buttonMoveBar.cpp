#include "buttonMoveBar.h"

#include "managerList.h"
#include "gFunc.h"

buttonMoveBar::buttonMoveBar(windowBase* bind) :
	buttonStatic(bind)
{
	_info.pos = D3DXVECTOR2(0, 0);
	_info.size = D3DXVECTOR2(_bindWindow->getInfo().size.x, BTN_MOVE_BAR_SIZE_Y);

	_activeSet.press = [this](void)->UI_LIST_NODE {
		if (gFunc::isMouseInRange(getAbsPos(), getAbsSize()))
		{
			_isClicked = true;
			_beforePos = MN_KEY->getMousePos();
		}
		return _bindWindow->getNode();
	};

	_activeSet.down = [this](void)->UI_LIST_NODE {
		if (_isClicked)
		{
			_bindWindow->getInfo().pos.x += MN_KEY->getMousePos().x - _beforePos.x;
			_bindWindow->getInfo().pos.y += MN_KEY->getMousePos().y - _beforePos.y;

			_beforePos = MN_KEY->getMousePos();
		}
		return _bindWindow->getNode();
	};

	_activeSet.up = [this](void)->UI_LIST_NODE {
		_isClicked = false;

		return _bindWindow->getNode();
	};
}

UI_LIST_NODE buttonMoveBar::updateActive(void)
{
	return buttonBase::updateActiveAnyway();
}