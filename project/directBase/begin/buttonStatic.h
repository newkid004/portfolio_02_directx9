#pragma once
#include "kGlobalDefine.h"
#include "buttonBase.h"

class buttonStatic : public buttonBase
{
public :
	virtual void updateAlways(void) override {};

public:
	buttonStatic(windowBase* bind) : buttonBase(bind) {};
	~buttonStatic() {};
};

