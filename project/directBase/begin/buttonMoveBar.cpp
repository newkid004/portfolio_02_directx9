#include "buttonMoveBar.h"

#include "managerList.h"

buttonMoveBar::buttonMoveBar(windowBase* bind) : 
	buttonStatic(bind)
{
	_info.pos = D3DXVECTOR2(0, 0);
	_info.size = D3DXVECTOR2(30, _bindWindow->getInfo().size.x);

	_activeSet.press = [this](void)->void {
		_beforePos = MN_KEY->getMousePos();
	};

	_activeSet.down = [this](void)->void {
		_bindWindow->getInfo().pos.x += _beforePos.x - MN_KEY->getMousePos().x;
		_bindWindow->getInfo().pos.y += _beforePos.y - MN_KEY->getMousePos().y;

		_beforePos = MN_KEY->getMousePos();
	};
}