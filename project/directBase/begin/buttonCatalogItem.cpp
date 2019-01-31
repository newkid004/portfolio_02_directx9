#include "buttonCatalogItem.h"

#include "gFunc.h"

#include "buttonMoveBar.h"
#include "buttonScrollVertical.h"

typedef windowBase::UI_LIST_NODE UI_LIST_NODE;

buttonCatalogItem::buttonCatalogItem(windowBase * bind, int index, float * bindOffset) :
	buttonBase(bind),
	_index(index),
	_bindOffset(bindOffset)
{
	_info.pos = D3DXVECTOR2(
		index % 4,
		index / 4);

	_info.size = D3DXVECTOR2(
		(bind->getInfo().size.x - BTN_SCROLL_SIZE_X) / 4.0f,
		(bind->getInfo().size.y - BTN_MOVE_BAR_SIZE_Y) / 4.0f);
}

UI_LIST_NODE buttonCatalogItem::updateAlways(void)
{
	auto absSize = getAbsSize();

	_info.pos.x = (_index % 4) * absSize.x;
	_info.pos.y = 
		((_index / 4) * absSize.y) -
		std::fmodf(*_bindOffset, absSize.y) +
		BTN_MOVE_BAR_SIZE_Y;

	return _bindWindow->getNode();
}

void buttonCatalogItem::drawUI(void)
{
	if (_info.backImage)
	{
		RECT clipRect = { 0, };
		RECT* pRect = nullptr;

		if (_index / 4 == 0)
		{
			clipRect.top = -(_info.pos.y - BTN_MOVE_BAR_SIZE_Y);
			pRect = &clipRect;
		}

		else if (3 < _index / 4)
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
