#include "buttonScrollVertical.h"

#include "managerList.h"
#include "gFunc.h"

#include "buttonMoveBar.h"

typedef windowBase::UI_LIST_NODE UI_LIST_NODE;

buttonScrollVerticalHead::buttonScrollVerticalHead(windowBase * bind) :
	buttonBase(bind)
{
	_activeSet.press = [this](void)->UI_LIST_NODE {
		if (gFunc::isMouseInRange(getAbsPos(), getAbsSize()))
		{
			_isClicked = true;
			_beforePosY = MN_KEY->getMousePos().y;
		}
		return _bindWindow->getNode();
	};

	_activeSet.down = [this](void)->UI_LIST_NODE {
		if (_isClicked)
		{
			LONG moveY = MN_KEY->getMousePos().y - _beforePosY;

			moveScroll(moveY);

			_beforePosY = MN_KEY->getMousePos().y;
		}
		return _bindWindow->getNode();
	};

	_activeSet.up = [this](void)->UI_LIST_NODE {
		_isClicked = false;

		return _bindWindow->getNode();
	};

	_info.size = D3DXVECTOR2(BTN_SCROLL_SIZE_X, 1.0f);
	_info.backImage = MN_SRC->getSpriteTexture("resource/texture/maptool/common/scrollVertical_button.png");
}

UI_LIST_NODE buttonScrollVerticalHead::updateAlways(void)
{
	if (gFunc::isMouseInRange(getAbsPos(), getAbsSize()))
		_info.alpha = min(1.0f, _info.alpha + MN_TIME->getDeltaTime() / 2.0f);
	else
		_info.alpha = max(0.5f, _info.alpha - MN_TIME->getDeltaTime() / 2.0f);

	return _bindWindow->getNode();
}

void buttonScrollVerticalHead::moveScroll(LONG interval)
{
	auto body = btnScrollFunc::b2Body(_body);

	// re position
	if (interval != 0)
	{
		_armTop->getInfo().scale.y += interval;
		_armBot->getInfo().pos.y += interval;
		_armBot->getInfo().scale.y -= interval;
		_info.pos.y += interval;
	}

	// re value
	float percent = 
		(_info.pos.y - BTN_MOVE_BAR_SIZE_Y) /
		(_body->getInfo().scale.y - _info.scale.y - BTN_MOVE_BAR_SIZE_Y);

	btnScrollFunc::b2Body(_body)->getValue() = percent;
}

// ----- scroll arm ----- //
buttonScrollVerticalArm::buttonScrollVerticalArm(windowBase * bind) :
	buttonStatic(bind)
{
	_info.size = D3DXVECTOR2(BTN_SCROLL_SIZE_X, 1.0f);
	_info.backImage = MN_SRC->getSpriteTexture("resource/texture/maptool/common/scrollVertical_body.png");
}

// ----- scroll body ----- //
buttonScrollVertical::buttonScrollVertical(windowBase * bind, int listHeight, float viewHeight) :
	buttonBase(bind)
{
	D3DXVECTOR2 textureSize;

	_info.backImage = MN_SRC->getSpriteTexture("resource/texture/maptool/common/scrollVertical_body.png");
	gFunc::getTextureSize(&textureSize, _info.backImage);

	_info.size = textureSize;
	_info.pos = D3DXVECTOR2(bind->getInfo().size.x - textureSize.x, BTN_MOVE_BAR_SIZE_Y);
	_info.scale.y = bind->getInfo().size.y - _info.pos.y;

	// ----- part ----- //
	_head = new buttonScrollVerticalHead(bind);
	_head->_armTop = _armTop = new buttonScrollVerticalArm(bind);
	_head->_armBot = _armBot = new buttonScrollVerticalArm(bind);

	// event
	_activeScrollSet.up = _armTop->getActiveSet().press = [this](void)->UI_LIST_NODE {
		_head->moveScroll(-10);

		return _bindWindow->getNode();
	};

	_activeScrollSet.down = _armBot->getActiveSet().press = [this](void)->UI_LIST_NODE {
		_head->moveScroll(10);

		return _bindWindow->getNode();
	};

	putListHeight(listHeight, viewHeight);
}

buttonScrollVertical::~buttonScrollVertical()
{
	SAFE_DELETE(_head);
	SAFE_DELETE(_armTop);
	SAFE_DELETE(_armBot);
}

UI_LIST_NODE buttonScrollVertical::updateAlways(void)
{
	return _head->updateAlways();
}

UI_LIST_NODE buttonScrollVertical::updateActice(void)
{
	if (gFunc::isMouseInRange(getAbsPos(), getAbsSize()))
	{
		_head->updateActice();
		_armTop->updateActice();
		_armBot->updateActice();
	}

	buttonBase::updateActiceScroll(this, _activeScrollSet);

	return _bindWindow->getNode();
}

void buttonScrollVertical::putListHeight(int ListHeight, float viewHeight)
{
	_listHeight = ListHeight;
	_viewHeight = viewHeight;

	_head->getInfo().scale.y = _info.scale.y / (_viewHeight / _listHeight);
	_head->getInfo().pos.y = BTN_MOVE_BAR_SIZE_Y + (_info.scale.y - _head->getInfo().scale.y) * _value;

	_armTop->getInfo().scale.y = _head->getInfo().pos.y - BTN_MOVE_BAR_SIZE_Y;

	_armBot->getInfo().pos.y = _head->getInfo().pos.y + _head->getInfo().scale.y;
	_armBot->getInfo().scale.y = _info.scale.y - _armBot->getInfo().pos.y;

	_head->moveScroll(0);
}

// ----- func ----- //
buttonScrollVerticalHead * btnScrollFunc::b2Head(buttonBase * btn)
{
	return (buttonScrollVerticalHead*)btn;
}

buttonScrollVerticalArm * btnScrollFunc::b2Arm(buttonBase * btn)
{
	return (buttonScrollVerticalArm*)btn;
}

buttonScrollVertical * btnScrollFunc::b2Body(buttonBase * btn)
{
	return (buttonScrollVertical*)btn;
}
