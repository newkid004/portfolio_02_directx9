#pragma once
#include "kGlobalDefine.h"

#include "maptool_data_catalog.h"

class windowBase;
class windowStatic;
class windowMoveable;
class windowRenderTarget;
class windowCtlogMaptool;

class buttonStatic;

class maptool_window
{
public :
	struct set
	{
		windowStatic* bottomTrans = nullptr;
		windowStatic* bottomBar = nullptr;
		windowRenderTarget* minimap = nullptr;

		windowCtlogMaptool* mv_prop = nullptr;
		windowCtlogMaptool* mv_character = nullptr;
		windowCtlogMaptool* mv_event = nullptr;
		windowMoveable* mv_file = nullptr;
		windowMoveable* mv_option = nullptr;

		windowCtlogMaptool* focusedWindow = nullptr;
	};

private :
	set _windowSet;

public :
	void update(void);

private :
	windowStatic* createBottomBar(void);
	windowRenderTarget* createMinimap(void);
	windowStatic* createBottomTrans(void);

	windowCtlogMaptool * create_mvProp(void);
	windowCtlogMaptool * create_mvCharacter(void);
	windowCtlogMaptool* create_mvEvent(void);
	windowMoveable* create_mvFile(void);
	windowMoveable* create_mvOption(void);

	buttonStatic* createButtonUnderBar(windowBase* bindWindow, const std::string & texture, float offsetNumber);

public :
	constexpr set & getSet(void) { return _windowSet; }

public:
	maptool_window();
	~maptool_window();
};

