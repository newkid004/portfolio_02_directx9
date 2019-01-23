#pragma once
#include "kGlobalDefine.h"
#include "baseObject.h"
#include "iRenderable.h"

class debugGizmo;

class renderObject : public baseObject, public iRenderable
{
protected:
	bool _isVisible = true;

public :	// iterface
	virtual void draw(void) final override;

protected:
	// ·»´õ 3´Ü°è
	virtual void drawPre(void) {};
	virtual void drawDo(void) {};
	virtual void drawPost(void) {};

public:
	bool getVisible(void) { return _isVisible; }

	void setVisible(bool input) { _isVisible = input; }

	void ToggleVisible(void) { _isVisible = !_isVisible; }

protected :
	renderObject();

public:
	~renderObject();
};