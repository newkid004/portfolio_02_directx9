#pragma once
#include "kGlobalDefine.h"

class windowBase;
class windowStatic;
class windowMoveable;
class windowRenderTarget;
class buttonStatic;

class maptool_window
{
public :
	struct set
	{
		windowStatic* bottomTrans = nullptr;
		windowStatic* bottomBar = nullptr;
		windowRenderTarget* minimap = nullptr;

		windowMoveable* mv_prop = nullptr;
		windowMoveable* mv_character = nullptr;
		windowMoveable* mv_event = nullptr;
		windowMoveable* mv_file = nullptr;
		windowMoveable* mv_option = nullptr;
	};

private :
	set _windowSet;

private :
	windowStatic* createBottomBar(void);
	windowRenderTarget* createMinimap(void);
	windowStatic* createBottomTrans(void);

	windowMoveable* create_mvProp(void);
	windowMoveable* create_mvCharacter(void);
	windowMoveable* create_mvEvent(void);
	windowMoveable* create_mvFile(void);
	windowMoveable* create_mvOption(void);

	buttonStatic* createButtonUnderBar(windowBase* bindWindow, const std::string & texture, float offsetNumber);

public :
	constexpr set & getSet(void) { return _windowSet; }

public:
	maptool_window();
	~maptool_window();
};

