#pragma once
#include "kGlobalDefine.h"
#include "windowBase.h"

class windowStatic : public windowBase
{
public :
	virtual UI_LIST_NODE updateWindow(void) override { return _managedNode; };

public:
	windowStatic(const uiInfo & info) : windowBase(info) {};
	~windowStatic() {};
};

