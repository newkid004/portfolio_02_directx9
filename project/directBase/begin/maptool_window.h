#pragma once
#include "kGlobalDefine.h"

class windowStatic;
class windowRenderTarget;

class maptool_window
{
private :
	windowStatic* _underBar = nullptr;
	windowRenderTarget* _minimap = nullptr;

private :
	windowStatic* createUnderBar(void);
	windowRenderTarget* createMinimap(void);

public:
	maptool_window();
	~maptool_window();
};

