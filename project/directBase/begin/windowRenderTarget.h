#pragma once
#include "kGlobalDefine.h"
#include "windowBase.h"

class windowRenderTarget : public windowBase
{
private :
	LPDIRECT3DSURFACE9 _depthStensil = nullptr;

public :
	virtual UI_LIST_NODE updateWindow(void) override { return _managedNode; };

public:
	windowRenderTarget(const uiInfo & info);
	~windowRenderTarget();
};

