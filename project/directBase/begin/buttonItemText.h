#pragma once
#include "kGlobalDefine.h"
#include "buttonItem.h"

class buttonItemText : public buttonItem
{
protected :
	std::string* _bindString = nullptr;

public :
	virtual void drawUI(void) override;

public :
	std::string*& getStringP(void) { return _bindString; }
	std::string & getString(void) { return *_bindString; }

public:
	buttonItemText(windowBase* bind, int index, int* bindIndex, float* bindOffset, D3DXVECTOR2 * bindRange);
	~buttonItemText();
};

