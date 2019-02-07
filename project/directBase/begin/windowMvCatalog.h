#pragma once
#include "kGlobalDefine.h"
#include "windowMoveable.h"

template<typename T>
class windowSelectionCatalog;

class buttonItem;
class buttonScrollVertical;

template<typename T>
class windowMvCatalog : public windowMoveable
{
protected :
	windowSelectionCatalog<T>* _selection = nullptr;
	buttonScrollVertical* _scroll = nullptr;

	int _selectIndex = -1;
	float _offset = 0.0f;
	D3DXVECTOR2 _range;

	std::vector<T> _vData;
	std::vector<buttonItem*> _vItem;

protected :
	virtual UI_LIST_NODE updateWindow(void) override;
	void updateControl(void);

	void drawUI(void) override;

protected :
	virtual LPDIRECT3DTEXTURE9 putTexture2button(int dataIndex) = 0;

public :
	constexpr int & getIndex(void) { return _selectIndex; }
	constexpr float & getOffset(void) { return _offset; }
	constexpr D3DXVECTOR2 & getRange(void) { return _range; }
	constexpr T & getItem(void) { return _vData[_selectIndex]; }

	void addItem(T input);

private :
	float rowCount(void) { return _vData.size() / (int)_range.y; }

protected:
	windowMvCatalog(const uiInfo & info, D3DXVECTOR2 & range);
	virtual ~windowMvCatalog();
};

#include "windowMvCatalog.hpp"