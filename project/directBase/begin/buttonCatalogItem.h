#pragma once
#include "kGlobalDefine.h"
#include "buttonStatic.h"

class buttonCatalogItem : public buttonBase
{
private:
	int _index;
	int * _bindIndex = nullptr;
	float* _bindOffset = nullptr;

protected :
	virtual UI_LIST_NODE updateAlways(void) override;

public :
	virtual void drawUI(void) override;

public:
	buttonCatalogItem(windowBase* bind, int index, int* bindIndex, float* bindOffset);
	~buttonCatalogItem() {};
};
