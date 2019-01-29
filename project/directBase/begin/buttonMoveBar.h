#pragma once
#include "kGlobalDefine.h"
#include "buttonStatic.h"

class buttonMoveBar : public buttonStatic
{
protected :
	POINT _beforePos;

public:
	buttonMoveBar(windowBase* bind);
	~buttonMoveBar() {};
};

