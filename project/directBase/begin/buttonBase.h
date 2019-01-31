#pragma once
#include "kGlobalDefine.h"

#include "windowBase.h"

class buttonBase
{
public :
	typedef windowBase::UI_LIST_NODE UI_LIST_NODE;

public :
	struct activeSet
	{
		std::function<UI_LIST_NODE(void)> up;
		std::function<UI_LIST_NODE(void)> press;
		std::function<UI_LIST_NODE(void)> down;
	};

	struct activeScrollSet
	{
		std::function<UI_LIST_NODE(void)> up;
		std::function<UI_LIST_NODE(void)> down;
	};

protected :
	uiInfo _info;
	activeSet _activeSet;

	windowBase* _bindWindow = nullptr;

public :
	virtual UI_LIST_NODE updateAlways(void) = 0;
	virtual UI_LIST_NODE updateActive(void);
	virtual UI_LIST_NODE updateActiveAnyway(void);
	static UI_LIST_NODE updateActiveScroll(buttonBase* own, activeScrollSet & scrollSet);
	static UI_LIST_NODE updateActiveScrollAnyway(buttonBase* own, activeScrollSet & scrollSet);
	virtual void drawUI(void);

public:
	uiInfo & getInfo(void) { return _info; }
	activeSet & getActiveSet(void) { return _activeSet; }
	windowBase*& getWindow(void) { return _bindWindow; }

	D3DXVECTOR2 getAbsPos(void);
	D3DXVECTOR2 getAbsSize(void);
	D3DXVECTOR2 getAbsScale(void);
	float getAbsAlpha(void) { return _bindWindow->getInfo().alpha * _info.alpha; };

public:
	buttonBase(windowBase* bind) : _bindWindow(bind) {};
	~buttonBase() {};
};

