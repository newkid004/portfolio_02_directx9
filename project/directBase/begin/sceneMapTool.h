#pragma once
#include "kGlobalDefine.h"
#include "sceneBase.h"

class maptool_window;
class maptool_field;
class maptool_render;
class maptool_io;

class maptool_brush;

class mapObject;

class staticMesh;
class skyBox;

class sceneMapTool : public sceneBase
{
public :
	maptool_window*	_window = nullptr;
	maptool_field*	_field = nullptr;
	maptool_render*	_render = nullptr;
	maptool_io*		_io = nullptr;

	STR_MAP(maptool_brush*) _mBrush;
	maptool_brush* _currentBrush = nullptr;

	mapObject* _mapObject = nullptr;
	skyBox* _skybox = nullptr;
private :
	POINT _mousePrev;

public:
	virtual void init(void) override;
	virtual void update(void) override;
	virtual void draw(void) override;
	virtual void drawUI(void) override;

private :
	void initMap(void);

	void updateControl_brush(void);

	void drawSelection(void);

	skyBox* createSkyBox(void);

public:
	sceneMapTool() {};
	~sceneMapTool();
};

