#pragma once
#include "kGlobalDefine.h"
#include "windowMoveable.h"

class windowSelection;

class buttonItemText;
class buttonScrollVertical;

class windowMvList : public windowMoveable
{
protected :
	windowSelection* _selection = nullptr;
	buttonScrollVertical* _scroll = nullptr;

	int _listCount = 20;

	int _selectIndex = -1;
	float _offset = 0.0f;

	std::vector<std::string> _vData;
	std::vector<buttonItemText*> _vItem;

protected:
	virtual UI_LIST_NODE updateWindow(void) override;
	void updateControl(void);

	void drawUI(void) override;

public:
	constexpr int & getIndex(void) { return _selectIndex; }
	constexpr float & getOffset(void) { return _offset; }
	constexpr int & getListCount(void) { return _listCount; }
	std::string & getItem(void) { return _vData[_selectIndex]; }

	void addItem(std::string & input);

private:
	float rowCount(void) { return _vData.size() / _listCount; }

public:
	windowMvList(const uiInfo & info, int listCount = -1);
	~windowMvList();
};

