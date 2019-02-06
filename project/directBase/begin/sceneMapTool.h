#pragma once
#include "kGlobalDefine.h"
#include "sceneBase.h"

class maptool_window;
class maptool_field;
class maptool_render;

class staticMesh;

class sceneMapTool : public sceneBase
{
private :
	maptool_window* _window = nullptr;
	maptool_field* _field = nullptr;
	maptool_render* _render = nullptr;

public:
	virtual void init(void) override;
	virtual void update(void) override;
	virtual void draw(void) override;
	virtual void drawUI(void) override;

private :
	void updateControl_Prop(void);

	void drawSelection(void);

public:
	sceneMapTool() {};
	~sceneMapTool();
};

