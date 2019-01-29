#include "windowRenderTarget.h"

#include "gFunc.h"

windowRenderTarget::windowRenderTarget(const uiInfo & info) : 
	windowBase(info)
{
	_info.backImage = gFunc::createRenderTarget();
	_depthStensil = gFunc::createDepthStensil();
}

windowRenderTarget::~windowRenderTarget()
{
	SAFE_RELEASE(_info.backImage);
	SAFE_RELEASE(_depthStensil);
}
