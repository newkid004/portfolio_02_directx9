#pragma once
#include "kGlobalDefine.h"

#include "maptool_data_catalog.h"

class windowBase;
class windowStatic;
class windowMoveable;
class windowRenderTarget;
class windowCtlogMaptool;
class windowMvList;

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
		windowCtlogMaptool* mv_bump = nullptr;
		windowCtlogMaptool* mv_node = nullptr;
		windowCtlogMaptool* mv_file = nullptr;
		windowMoveable* mv_option = nullptr;

		windowCtlogMaptool* focusedWindow = nullptr;
	};

private :
	set _windowSet;

	int _activeWindow = 0;

public :
	void update(void);

private :
	windowStatic* createBottomBar(void);
	windowRenderTarget* createMinimap(void);
	windowStatic* createBottomTrans(void);

	windowCtlogMaptool * create_mvProp(void);
	windowCtlogMaptool * create_mvBump(void);
	windowCtlogMaptool* create_mvNode(void);
	windowCtlogMaptool* create_mvFile(void);
	windowMoveable* create_mvOption(void);

	void createContent_prop(std::vector<maptool_data_catalog::OBJ::PROP*> & vContent);
	void createContent_bump(std::vector<maptool_data_catalog::OBJ::BUMP*> & vContent);
	void createContent_node(std::vector<maptool_data_catalog::OBJ::NODE*> & vContent);
	void createContent_file(std::vector<maptool_data_catalog::OBJ::FILE*> & vContent);
	void createContent_option(std::vector<maptool_data_catalog::OBJ::PROP*> & vContent);

	buttonStatic* createButtonUnderBar(windowBase* bindWindow, const std::string & texture, float offsetNumber);

public :
	constexpr set & getSet(void) { return _windowSet; }

public:
	maptool_window();
	~maptool_window();
};

