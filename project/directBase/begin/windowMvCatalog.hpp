#include "windowMvCatalog.h"

#include "managerList.h"

#include "gFunc.h"

#include "windowSelectionCatalog.h"

#include "buttonMoveBar.h"
#include "buttonScrollVertical.h"
#include "buttonItem.h"

typedef windowBase::UI_LIST_NODE UI_LIST_NODE;

template<typename T>
windowMvCatalog<T>::windowMvCatalog(const uiInfo & info, D3DXVECTOR2 & range) :
	windowMoveable(info),
	_range(range)
{
	_scroll = (buttonScrollVertical*)addButton("scroll", new buttonScrollVertical(this, _range.y, _range.y));
	_selection =  new windowSelectionCatalog<T>(info, this);
	_selection->init(_range.x, _range.y);

	for (int i = 0; i < (_range.x + 1) * _range.y; ++i)
	{
		auto btn = new buttonItem(this, i, &_selectIndex, &_offset, &_range);
		_vItem.push_back(btn);

		char buf[64];
		sprintf_s(buf, "item_%d", i);
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
		_scroll->getValue() * (rowCount() / _range.y);

	float btnSize = (_info.size.y - BTN_MOVE_BAR_SIZE_Y) / _range.y;
	float modOffset = std::fmodf(_offset, btnSize);
	for (int i = 0; i < (_range.x + 1) * _range.y; ++i)
	{
		int dataIndex = std::fmodf(i, _range.x) + ((_offset - modOffset + (btnSize * (i / (int)_range.x))) / btnSize) * (int)_range.y;

		if (dataIndex < _vData.size())
		{
			auto & btnInfo = _vItem[i]->getInfo();
			auto texture = btnInfo.backImage = putTexture2button(dataIndex);
			
			D3DXVECTOR2 texSize;
			gFunc::getTextureSize(&texSize, texture);

			btnInfo.scale = D3DXVECTOR2(
				btnSize / texSize.x, 
				btnSize / texSize.y);
			btnInfo.size = texSize;
		}
		else
			_vItem[i]->getInfo().backImage = nullptr;
	}

	updateControl();
	_selection->updateWindow();

	return _managedNode;
}

template<typename T>
inline void windowMvCatalog<T>::updateControl(void)
{
	if (gFunc::isMouseInRange(_info.pos, getAbsSize()))
	{
		if (MN_KEY->wheelUp())		_scroll->moveScroll(-10);
		if (MN_KEY->wheelDown())	_scroll->moveScroll(10);
	}

	// 선택 취소
	if (MN_KEY->mouseDown(EMouseInput::RIGHT)) _selectIndex = -1;
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
	int listItemRows = rows < _range.y ? _range.y : rows;

	_scroll->putListHeight(listItemRows, _range.y);
}