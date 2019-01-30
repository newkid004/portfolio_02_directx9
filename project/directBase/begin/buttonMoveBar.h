#pragma once
#include "kGlobalDefine.h"
#include "buttonStatic.h"

constexpr float BTN_MOVE_BAR_SIZE = 30.0f;

class buttonMoveBar : public buttonStatic
{
protected :
	bool _isClicked = false;
	POINT _beforePos;

public :
	virtual UI_LIST_NODE updateActice(void) override;

public:
	buttonMoveBar(windowBase* bind);
	~buttonMoveBar() {};
};

