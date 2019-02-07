#pragma once
#include "kGlobalDefine.h"
#include "buttonBase.h"

class buttonItem : public buttonBase
{
protected:
	D3DXVECTOR2 _viewCount;

	int _index;
	int * _bindIndex = nullptr;
	float* _bindOffset = nullptr;

protected:
	virtual UI_LIST_NODE updateAlways(void) override;

public:
	virtual void drawUI(void) override;

public:
	buttonItem(windowBase* bind, int index, int* bindIndex, float* bindOffset, int countX, int countY);
	~buttonItem() {};
};

