#include "windowMvCatalog.h"

#include "managerList.h"

#include "gFunc.h"

#include "windowSelectionCatalog.h"

#include "buttonMoveBar.h"
#include "buttonScrollVertical.h"
#include "buttonItem.h"

typedef windowBase::UI_LIST_NODE UI_LIST_NODE;

template<typename T>
windowMvCatalog<T>::windowMvCatalog(const uiInfo & info) :
	windowMoveable(info)
{
	_scroll = (buttonScrollVertical*)addButton("scroll", new buttonScrollVertical(this, 4, 4));
	_selection =  new windowSelectionCatalog<T>(info, this);
	_selection->init(4, 4);

	for (int i = 0; i < 20; ++i)
	{
		auto btn = new buttonItem(this, i, &_selectIndex, &_offset, 4, 4);
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
		_scroll->getValue() * (rowCount() / 4.0f);

	float btnSize = (_info.size.y - BTN_MOVE_BAR_SIZE_Y) / 4.0f;
	float modOffset = std::fmodf(_offset, btnSize);
	for (int i = 0; i < 20; ++i)
	{
		int dataIndex = (i % 4) + ((_offset - modOffset + (btnSize * (i / 4))) / btnSize) * 4;

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
	int listItemRows = rows < 4 ? 4 : rows;

	_scroll->putListHeight(listItemRows, 4);
}