#pragma once
#include "kGlobalDefine.h"
#include "baseObject.h"
#include "iRenderable.h"

class UIBase : public baseObject, public iRenderable
{
protected:
	bool _isVisible = false;
	D3DCOLOR _diffuseColor;

public :
	virtual void draw(void) final override {};
	virtual void drawUI(void) final override;

public :
	bool getVisible(void) { return _isVisible; }
	void setVisible(bool input) { _isVisible = input; }

	D3DCOLOR getColor(void) { return _diffuseColor; }
	void setColor(D3DCOLOR input) { _diffuseColor = input; }

protected :
	virtual void drawDoUI(void) {};

protected :
	UIBase();
	~UIBase();
};

