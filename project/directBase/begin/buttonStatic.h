#pragma once
#include "kGlobalDefine.h"
#include "buttonBase.h"

class buttonStatic : public buttonBase
{
public :
	virtual UI_LIST_NODE updateAlways(void) override { return _bindWindow->getNode(); }

public:
	buttonStatic(windowBase* bind) : buttonBase(bind) {};
	~buttonStatic() {};
};

