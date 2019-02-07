#pragma once
#include "kGlobalDefine.h"
#include "windowStatic.h"

class windowSelection : public windowStatic
{
protected:
	bool _isVisible = false;

	int* _bindIndex = nullptr;
	float* _bindOffset = nullptr;
	windowBase* _bindWindow = nullptr;

	D3DXVECTOR2 _viewCount;

public:
	void init(int viewX, int viewY);
	virtual void drawUI(void) override;

protected:
	virtual void initBind(void) {};
	void resize(int viewX, int viewY);

public :
	UI_LIST_NODE updateWindow(void) override;
	UI_LIST_NODE updateFocus(void) override { return _bindWindow->getNode(); }

public :
	int*& getBindIndex(void) { return _bindIndex; }
	float*& getBindOffset(void) { return _bindOffset; }

public :
	windowSelection(const uiInfo & info, windowBase* bindWindow);
	virtual ~windowSelection() {};
};