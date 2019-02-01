#pragma once
#include "kGlobalDefine.h"
#include "buttonBase.h"

class IbuttonScroll
{
protected :
	buttonBase* _bindButton = nullptr;
	buttonBase::activeScrollSet _activeScrollSet;

public :
	windowBase::UI_LIST_NODE updateActiveScroll(void);
	windowBase::UI_LIST_NODE updateActiveScrollAnyway(void);

public :
	buttonBase::activeScrollSet & getActiveScrollSet(void) { return _activeScrollSet; }

public:
	IbuttonScroll(buttonBase* bindButton);
	virtual ~IbuttonScroll();
};

