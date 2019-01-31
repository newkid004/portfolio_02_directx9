#pragma once
#include "kGlobalDefine.h"
#include "windowMoveable.h"

class buttonCatalogItem;
class buttonScrollVertical;

template<typename T>
class windowMvCatalog : public windowMoveable
{
protected :
	buttonScrollVertical* _scroll = nullptr;

	int _selectIndex = 0;
	float _offset = 0.0f;

	std::vector<T> _vData;
	std::vector<buttonCatalogItem*> _vCatalog;

protected :
	virtual UI_LIST_NODE updateWindow(void) override;

protected :
	buttonCatalogItem* createButtonCatalog(int index);
	virtual LPDIRECT3DTEXTURE9 putTexture2button(int dataIndex) = 0;

public :
	int getIndex(void) { return _selectIndex; }
	T getItem(void) { return _vData[_selectIndex]; }

	void addItem(T input);

private :
	float rowCount(void) { return _vData.size() / 4; }

protected:
	windowMvCatalog(const uiInfo & info);
	~windowMvCatalog();
};

#include "windowMvCatalog.hpp"