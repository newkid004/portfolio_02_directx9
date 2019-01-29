#include "maptool_window.h"

#include "managerList.h"

#include "windowStatic.h"
#include "windowRenderTarget.h"

#include "buttonStatic.h"

maptool_window::maptool_window()
{
	_underBar = createUnderBar();
	_minimap = createMinimap();
}

maptool_window::~maptool_window()
{
	SAFE_DELETE(_underBar);
	SAFE_DELETE(_minimap);
}

windowStatic * maptool_window::createUnderBar(void)
{
	uiInfo winInfo;
	winInfo.scale = D3DXVECTOR2(
		WINSIZEX / 2.0f,
		WINSIZEY / 10.0f );
	winInfo.pos = D3DXVECTOR2(
		(WINSIZEX + winInfo.scale.x) / 2.0f,
		WINSIZEY - winInfo.scale.y );
	
	windowStatic* result = new windowStatic(winInfo);

	vector<buttonStatic*> vButton;

	return result;
}

windowRenderTarget * maptool_window::createMinimap(void)
{
	uiInfo winInfo;
	winInfo.scale = D3DXVECTOR2(
		WINSIZEX * 0.21f,
		WINSIZEY * 0.363);
	winInfo.pos = D3DXVECTOR2(WINSIZEX - winInfo.scale.x, 0);

	return new windowRenderTarget(winInfo);
}