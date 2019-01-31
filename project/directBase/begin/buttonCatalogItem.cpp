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
	_info.pos.y = 
		((_index / 4) * _info.size.y) -
		std::fmodf(*_bindOffset, _info.size.y);

	return _bindWindow->getNode();
}

void buttonCatalogItem::drawUI(void)
{
	if (_info.backImage)
	{
		gFunc::drawSprite(
			_info.backImage,
			getAbsPos(),
			getAbsSize(),
			getAbsScale(),
			getAbsAlpha());
	}
}
