#pragma once
#include "kGlobalDefine.h"
#include "windowMoveable.h"

template<typename T>
class windowSelection;

class buttonCatalogItem;
class buttonScrollVertical;

template<typename T>
class windowMvCatalog : public windowMoveable
{
protected :
	windowSelection<T>* _selection = nullptr;
	buttonScrollVertical* _scroll = nullptr;

	int _selectIndex = -1;
	float _offset = 0.0f;

	std::vector<T> _vData;
	std::vector<buttonCatalogItem*> _vCatalog;

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

// ----- selection ----- //
template<typename T>
class windowSelection : public windowStatic
{
public :
	// ----- 해당 클래스 내부에서만 사용 ----- //
	friend windowMvCatalog<T>;

private:
	bool _isVisible = false;
	int* _bindIndex = nullptr;
	float* _bindOffset = nullptr;
	windowMvCatalog<T>* _bindWindow = nullptr;

public :
	void drawUI(void) override;

protected:
	UI_LIST_NODE updateWindow(void) override;
	UI_LIST_NODE updateFocus(void) override { return _bindWindow->getNode(); }

protected:
	windowSelection(const uiInfo & info, windowMvCatalog<T>* bindWindow);
	virtual ~windowSelection() {};
};

#include "windowMvCatalog.hpp"
