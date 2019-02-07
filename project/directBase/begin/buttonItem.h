#pragma once
#include "kGlobalDefine.h"
#include "buttonBase.h"

class buttonItem : public buttonBase
{
protected:
	int _index;

	int * _bindIndex = nullptr;
	float* _bindOffset = nullptr;
	D3DXVECTOR2* _bindRange = nullptr;

protected:
	virtual UI_LIST_NODE updateAlways(void) override;

public:
	virtual void drawUI(void) override;

public:
	buttonItem(windowBase* bind, int index, int* bindIndex, float* bindOffset, D3DXVECTOR2* bindRange);
	~buttonItem() {};
};

