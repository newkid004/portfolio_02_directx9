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

	_info.pos.x = bind->getInfo().size.x - BTN_SCROLL_SIZE_X;
	_info.size = D3DXVECTOR2(BTN_SCROLL_SIZE_X, 1.0f);
	_info.backImage = MN_SRC->getSpriteTexture("resource/texture/maptool/common/scrollVertical_button.png");
}

UI_LIST_NODE buttonScrollVerticalHead::updateAlways(void)
{
	if (_isClicked || gFunc::isMouseInRange(getAbsPos(), getAbsSize()))
		_info.alpha = min(1.0f, _info.alpha + MN_TIME->getDeltaTime() * 2.0f);
	else
		_info.alpha = max(0.5f, _info.alpha - MN_TIME->getDeltaTime() * 2.0f);

	return _bindWindow->getNode();
}

UI_LIST_NODE buttonScrollVerticalHead::updateActive(void)
{
	return buttonBase::updateActiveAnyway();
}

void buttonScrollVerticalHead::moveScroll(LONG interval)
{
	auto & scrollValue = btnScrollFunc::b2Body(_body)->getValue();
	auto body = btnScrollFunc::b2Body(_body);

	if (_info.size.y == body->getInfo().size.y)
		return;

	bool isCorrect = false;

	// re position
	if (interval != 0)
	{
		if (interval < 0 && (_info.pos.y - BTN_MOVE_BAR_SIZE_Y) < 0.0f)
		{
			moveScroll(interval + 1);
			return;
		}
		else if (0 < interval && 1.0f <= scrollValue)
		{
			moveScroll(interval - 1);
			return;
		} 

		_armTop->getInfo().scale.y = max(BTN_MOVE_BAR_SIZE_Y, _armTop->getInfo().scale.y + interval);
		_armBot->getInfo().pos.y += interval;
		_armBot->getInfo().scale.y -= interval;
		_info.pos.y += interval;
	}

	// re value
	float maxLength = _body->getInfo().scale.y - _info.scale.y;

	if (maxLength != 0.0f)
		scrollValue = (_info.pos.y - BTN_MOVE_BAR_SIZE_Y) / maxLength;
}

// ----- scroll arm ----- //
buttonScrollVerticalArm::buttonScrollVerticalArm(windowBase * bind) :
	buttonStatic(bind)
{
	_info.pos.x = bind->getInfo().size.x - BTN_SCROLL_SIZE_X;
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
	_head->_body = this;
	_head->_armTop = _armTop = new buttonScrollVerticalArm(bind);
	_head->_armBot = _armBot = new buttonScrollVerticalArm(bind);

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

UI_LIST_NODE buttonScrollVertical::updateActive(void)
{
	_head->updateActive();
	_armTop->updateActive();
	_armBot->updateActive();

	return _bindWindow->getNode();
}

void buttonScrollVertical::drawUI(void)
{
	buttonBase::drawUI();

	_armTop->drawUI();
	_armBot->drawUI();
	_head->drawUI();
}

void buttonScrollVertical::putListHeight(int ListHeight, float viewHeight)
{
	_listHeight = ListHeight;
	_viewHeight = viewHeight;

	_armTop->getInfo().scale.y = _head->getInfo().pos.y - BTN_MOVE_BAR_SIZE_Y;

	_head->getInfo().scale.y = _info.scale.y * (_viewHeight / _listHeight);
	_head->getInfo().pos.y = _info.scale.y - _head->getInfo().scale.y != 0 ?
		BTN_MOVE_BAR_SIZE_Y + ((_head->getInfo().pos.y - BTN_MOVE_BAR_SIZE_Y) / (_info.scale.y - _head->getInfo().scale.y)) * _value :
		BTN_MOVE_BAR_SIZE_Y;

	_armBot->getInfo().pos.y = _head->getInfo().pos.y + _head->getInfo().scale.y;
	_armBot->getInfo().scale.y = _bindWindow->getInfo().size.y - _armBot->getInfo().pos.y;

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
