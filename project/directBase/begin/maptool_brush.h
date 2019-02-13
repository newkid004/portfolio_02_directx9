#pragma once
#include "kGlobalDefine.h"

class sceneMapTool;

class windowCtlogMaptool;

class maptool_window;
class maptool_field;
class maptool_io;

class maptool_brush
{
public :
	struct set
	{
		windowCtlogMaptool** bindWindow	= nullptr;	// focused window

		maptool_window*	data_window		= nullptr;
		maptool_field*	data_field		= nullptr;
		maptool_io*		data_io			= nullptr;
	};

protected :
	set _set;

	static POINT _mousePrev;

public :
	void update(void);

protected :
	virtual void updateMouse(void);
	virtual void updateKey(void);

protected :
	// mouse
	virtual void updatePickObject(void);
	virtual void updateReleaseSelection(void);
	virtual void updateObjectMove(POINT & mouseMove);
	virtual void updateObjectRotate(POINT & mouseMove);
	virtual void updateObjectScale(void);

	// key
	virtual void updateWindowClose(void);
	virtual void updateIO(void);
	virtual void updateObjectDelete(void);

	// mouse active
	virtual void putObject(void) = 0;

public:
	maptool_brush(sceneMapTool* viewData);
	~maptool_brush() {};
};