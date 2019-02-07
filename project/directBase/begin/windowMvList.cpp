#include "windowMvList.h"

#include "managerList.h"

#include "gFunc.h"

#include "windowSelection.h"

#include "buttonMoveBar.h"
#include "buttonScrollVertical.h"
#include "buttonItemText.h"

typedef windowBase::UI_LIST_NODE UI_LIST_NODE;

windowMvList::windowMvList(const uiInfo & info, int listCount) :
	windowMoveable(info)
{
	_listCount = listCount < 0 ? 20 : listCount;

	_scroll = (buttonScrollVertical*)addButton("scroll", new buttonScrollVertical(this, _listCount, _listCount));
	_selection = new windowSelection(info, this);
	_selection->init(1, _listCount);
	
	// initBind
	_selection->getBindIndex() = &_selectIndex;
	_selection->getBindOffset() = &_offset;

	for (int i = 0; i < _listCount + 1; ++i)
	{
		auto btn = new buttonItemText(this, i, &_selectIndex, &_offset, _listCount);
	
		_vItem.push_back(btn);
	
		char buf[64];
		sprintf_s(buf, "item_%d", i);
		addButton(buf, btn);
	}
}

windowMvList::~windowMvList()
{
	SAFE_DELETE(_selection);
}

UI_LIST_NODE windowMvList::updateWindow(void)
{
	_offset =
		(_info.size.y - BTN_MOVE_BAR_SIZE_Y) *
		_scroll->getValue() * (rowCount() / _listCount);

	float btnSize = (_info.size.y - BTN_MOVE_BAR_SIZE_Y) / (float)_listCount;
	float modOffset = std::fmodf(_offset, btnSize);
	for (int i = 0; i < _listCount + 1; ++i)
	{
		int dataIndex = i + (_offset - modOffset + (btnSize * i)) / btnSize;

		if (dataIndex < _vData.size())
			_vItem[i]->getStringP() = &_vData[dataIndex];
		else
			_vItem[i]->getStringP() = nullptr;
	}

	updateControl();
	_selection->updateWindow();

	return _managedNode;
}

void windowMvList::updateControl(void)
{
	if (gFunc::isMouseInRange(_info.pos, getAbsSize()))
	{
		if (MN_KEY->wheelUp())		_scroll->moveScroll(-10);
		if (MN_KEY->wheelDown())	_scroll->moveScroll(10);
	}

	// 선택 취소
	if (MN_KEY->mouseDown(EMouseInput::RIGHT)) _selectIndex = -1;
}

void windowMvList::drawUI(void)
{
	windowMoveable::drawUI();
	_selection->drawUI();
}

void windowMvList::addItem(std::string & input)
{
	_vData.push_back(input);

	int rows = _listCount;
	int listItemRows = rows < 20 ? 20 : rows;

	_scroll->putListHeight(listItemRows, _listCount);
}
