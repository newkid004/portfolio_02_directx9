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
		windowCtlogMaptool* mv_trigger = nullptr;
		windowCtlogMaptool* mv_spawner = nullptr;
		windowCtlogMaptool* mv_file = nullptr;

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
	windowCtlogMaptool* create_mvTrigger(void);
	windowCtlogMaptool* create_mvSpawner(void);
	windowCtlogMaptool* create_mvFile(void);

	void createContent_prop(std::vector<maptool_data_catalog::OBJ::PROP*> & vContent);
	void createContent_bump(std::vector<maptool_data_catalog::OBJ::BUMP*> & vContent);
	void createContent_node(std::vector<maptool_data_catalog::OBJ::NODE*> & vContent);
	void createContent_trigger(std::vector<maptool_data_catalog::OBJ::TRIGGER*> & vContent);
	void createContent_spawner(std::vector<maptool_data_catalog::OBJ::SPAWNER*> & vContent);

	buttonStatic* createButtonUnderBar(windowBase* bindWindow, const std::string & texture, float offsetNumber);

public :
	constexpr set & getSet(void) { return _windowSet; }

public:
	maptool_window();
	~maptool_window();
};

