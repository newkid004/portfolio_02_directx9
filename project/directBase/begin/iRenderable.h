#pragma once
#include "kGlobalDefine.h"

class iRenderable
{
public:
	virtual void draw(void) = 0;	// require
	virtual void drawUI(void) {}	// optional
};

