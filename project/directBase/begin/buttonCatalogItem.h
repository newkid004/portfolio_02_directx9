#pragma once
#include "kGlobalDefine.h"
#include "buttonItem.h"

class buttonCatalogItem : public buttonItem
{
public:
	buttonCatalogItem(windowBase* bind, int index, int* bindIndex, float* bindOffset);
	~buttonCatalogItem() {};
};

