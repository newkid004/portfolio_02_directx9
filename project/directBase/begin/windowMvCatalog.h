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
	constexpr T & getItem(void) { return _vData[_selectIndex]; }

	void addItem(T input);

private :
	float rowCount(void) { return _vData.size() / 4; }

protected:
	windowMvCatalog(const uiInfo & info);
	virtual ~windowMvCatalog();
};

#include "windowMvCatalog.hpp"