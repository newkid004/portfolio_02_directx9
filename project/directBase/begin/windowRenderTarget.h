#pragma once
#include "kGlobalDefine.h"
#include "windowBase.h"

class windowRenderTarget : public windowBase
{
private :
	LPDIRECT3DSURFACE9 _depthStensil = nullptr;

public :
	virtual void updateWindow(void) override {};

public:
	windowRenderTarget(const uiInfo & info);
	~windowRenderTarget();
};

