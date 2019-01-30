#include "windowRenderTarget.h"

#include "gFunc.h"

windowRenderTarget::windowRenderTarget(const uiInfo & info) : 
	windowBase(info)
{
	_info.backImage = gFunc::createRenderTarget(info.size);
	_depthStensil = gFunc::createDepthStensil(info.size);

	gFunc::runRenderTarget(_info.backImage, D3DCLEAR_TARGET, NULL, [](void)->void {}, COLOR_BLACK(0));
}

windowRenderTarget::~windowRenderTarget()
{
	SAFE_RELEASE(_info.backImage);
	SAFE_RELEASE(_depthStensil);
}
