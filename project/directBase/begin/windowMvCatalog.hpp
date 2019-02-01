#include "windowMvCatalog.h"

#include "managerList.h"

#include "gFunc.h"

#include "buttonMoveBar.h"
#include "buttonScrollVertical.h"
#include "buttonCatalogItem.h"

typedef windowBase::UI_LIST_NODE UI_LIST_NODE;

template<typename T>
windowMvCatalog<T>::windowMvCatalog(const uiInfo & info) :
	windowMoveable(info)
{
	_selection =  new windowSelection<T>(info, this);
	_scroll = (buttonScrollVertical*)addButton("scroll", new buttonScrollVertical(this, 4, 4));

	for (int i = 0; i < 20; ++i)
	{
		auto btn = new buttonCatalogItem(this, i, &_selectIndex, &_offset);

		_vCatalog.push_back(btn);

		char buf[64];
		sprintf_s(buf, "Catalog_%d", i);
		addButton(buf, btn);
	}
}

template<typename T>
windowMvCatalog<T>::~windowMvCatalog()
{
	SAFE_DELETE(_selection);

	for (auto i : _vData)
		SAFE_DELETE(i);
}

template<typename T>
inline UI_LIST_NODE windowMvCatalog<T>::updateWindow(void)
{
	_offset = 
		(_info.size.y - BTN_MOVE_BAR_SIZE_Y) *
		_scroll->getValue() * (rowCount() / 4.0f);

	float btnSize = (_info.size.y - BTN_MOVE_BAR_SIZE_Y) / 4.0f;
	float modOffset = std::fmodf(_offset, btnSize);
	for (int i = 0; i < 20; ++i)
	{
		int dataIndex = (i % 4) + ((_offset - modOffset + (btnSize * (i / 4))) / btnSize) * 4;

		if (dataIndex < _vData.size())
		{
			auto & btnInfo = _vCatalog[i]->getInfo();
			auto texture = btnInfo.backImage = putTexture2button(dataIndex);
			
			D3DXVECTOR2 texSize;
			gFunc::getTextureSize(&texSize, texture);

			btnInfo.scale = D3DXVECTOR2(
				btnSize / texSize.x, 
				btnSize / texSize.y);
			btnInfo.size = texSize;
		}
		else
			_vCatalog[i]->getInfo().backImage = nullptr;
	}

	updateScroll();
	_selection->updateWindow();

	return _managedNode;
}

template<typename T>
inline void windowMvCatalog<T>::updateScroll(void)
{
	if (gFunc::isMouseInRange(_info.pos, getAbsSize()))
	{
		if (MN_KEY->wheelUp())		_scroll->moveScroll(-10);
		if (MN_KEY->wheelDown())	_scroll->moveScroll(10);
	}
}

template<typename T>
inline void windowMvCatalog<T>::drawUI(void)
{
	windowMoveable::drawUI();
	_selection->drawUI();
}

template<typename T>
inline void windowMvCatalog<T>::addItem(T input)
{
	_vData.push_back(input);

	int rows = rowCount();
	int listItemRows = rows < 4 ? 4 : rows;

	_scroll->putListHeight(listItemRows, 4);
}

// ----- selection ----- //

template<typename T>
inline windowSelection<T>::windowSelection(const uiInfo & info, windowMvCatalog<T> * bindWindow) :
	windowStatic(info),
	_bindWindow(bindWindow)
{
	_bindIndex = &bindWindow->getIndex();
	_bindOffset = &bindWindow->getOffset();

	_info.size = D3DXVECTOR2(
		(info.size.x - BTN_SCROLL_SIZE_X) / 4.0f,
		(info.size.y - BTN_MOVE_BAR_SIZE_Y) / 4.0f);

	_info.backImage = MN_SRC->getSpriteTexture("resource/texture/maptool/common/catalog_outline.png");
}

template<typename T>
inline void windowSelection<T>::drawUI(void)
{
	if (_isVisible && 0 <= *_bindIndex)
	{
		RECT clipRect = { 0, };

		if (_info.pos.y < BTN_MOVE_BAR_SIZE_Y)
			clipRect.top = std::fmodf(*_bindOffset, _info.size.y);
		else if (_bindWindow->getInfo().size.y < _info.pos.y + _info.size.y)
			clipRect.bottom = (_info.pos.y + _info.size.y) - _bindWindow->getInfo().size.y;

		gFunc::drawSprite(
			_info.backImage,
			_info.pos + _bindWindow->getInfo().pos,
			_info.size,
			_info.scale,
			_info.alpha,
			NULL,
			&clipRect, false);
	}
}

template<typename T>
inline UI_LIST_NODE windowSelection<T>::updateWindow(void)
{
	_info.alpha = (std::cosf(MN_TIME->getRunningTime() * 3.0f) + 1.0f) / 2.0f;

	_info.pos.x = (*_bindIndex % 4) * _info.size.x;
	_info.pos.y = (*_bindIndex / 4) * _info.size.y - *_bindOffset + BTN_MOVE_BAR_SIZE_Y;

	_isVisible = true;
	if (_info.pos.y + _info.size.y <= BTN_MOVE_BAR_SIZE_Y)
		_isVisible = false;
	else if (_bindWindow->getInfo().size.y <= _info.pos.y)
		_isVisible = false;

	return _bindWindow->getNode();
}
