#pragma once
#include "kGlobalDefine.h"

#include "windowBase.h"

struct activeSet
{
	std::function<void(void)> up;
	std::function<void(void)> press;
	std::function<void(void)> down;
};

class buttonBase
{
protected :
	uiInfo _info;
	activeSet _activeSet;

	windowBase* _bindWindow = nullptr;

public :
	virtual void updateAlways(void) = 0;
	virtual void updateActice(void);
	virtual void drawUI(void);

public:
	const uiInfo & getInfo(void) { return _info; }
	activeSet & getActiveSet(void) { return _activeSet; }
	windowBase*& getWindow(void) { return _bindWindow; }

public:
	buttonBase(windowBase* bind) : _bindWindow(bind) {};
	~buttonBase() {};
};

