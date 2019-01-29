#pragma once
#include "kGlobalDefine.h"
#include "windowBase.h"

class windowStatic : public windowBase
{
public :
	virtual void updateWindow(void) override {};

public:
	windowStatic(const uiInfo & info) : windowBase(info) {};
	~windowStatic() {};
};

