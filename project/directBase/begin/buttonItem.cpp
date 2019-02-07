#include "buttonItem.h"

#include "gFunc.h"

#include "buttonMoveBar.h"
#include "buttonScrollVertical.h"

typedef windowBase::UI_LIST_NODE UI_LIST_NODE;

buttonItem::buttonItem(windowBase * bind, int index, int * bindIndex, float * bindOffset, D3DXVECTOR2 * bindRange) :
	buttonBase(bind),
	_index(index),
	_bindIndex(bindIndex),
	_bindOffset(bindOffset),
	_bindRange(bindRange)
{
	_info.pos = D3DXVECTOR2(
		std::fmodf(index, _bindRange->x),
		index / _bindRange->x);

	_info.size = D3DXVECTOR2(
		(bind->getInfo().size.x - BTN_SCROLL_SIZE_X) /_bindRange->x,
		(bind->getInfo().size.y - BTN_MOVE_BAR_SIZE_Y) / _bindRange->y);

	_info.pos = gFunc::Vec2Mlt(_info.pos, _info.size);

	_activeSet.press = [this](void)->UI_LIST_NODE {
		if (_info.backImage)
			*_bindIndex = _index + (int)(*_bindOffset / getAbsSize().y) * (int)_bindRange->x;

		return _bindWindow->getNode();
	};
}

UI_LIST_NODE buttonItem::updateAlways(void)
{
	auto absSize = getAbsSize();

	_info.pos.x = (std::fmodf(_index, _bindRange->x)) * absSize.x;
	_info.pos.y =
		((_index / (int)_bindRange->x) * absSize.y) -
		std::fmodf(*_bindOffset, absSize.y) +
		BTN_MOVE_BAR_SIZE_Y;

	return _bindWindow->getNode();
}

void buttonItem::drawUI(void)
{
	if (_info.backImage)
	{
		RECT clipRect = { 0, };
		RECT* pRect = nullptr;

		if (_index / (int)_bindRange->x == 0)
		{
			clipRect.top = -(_info.pos.y - BTN_MOVE_BAR_SIZE_Y);
			pRect = &clipRect;
		}

		else if (_bindRange->y - 1.0f < _index / (int)_bindRange->x)
		{
			if (_bindWindow->getInfo().size.y <= _info.pos.y)
				return;

			auto absSize = getAbsSize().y;
			clipRect.bottom = std::fmodf(_info.pos.y - BTN_MOVE_BAR_SIZE_Y, absSize);
			pRect = &clipRect;
		}

		gFunc::drawSprite(
			_info.backImage,
			getAbsPos(),
			getAbsSize(),
			getAbsScale(),
			getAbsAlpha(),
			NULL,
			pRect, false);
	}
}