#pragma once
#include "kGlobalDefine.h"
#include "sceneBase.h"

class maptool_data;
class maptool_window;

class sceneMapTool : public sceneBase
{
private :
	maptool_window* _window = nullptr;

public:
	virtual void init(void) override;
	virtual void update(void) override;
	virtual void draw(void) override;
	virtual void drawUI(void) override;

public:
	sceneMapTool() {};
	~sceneMapTool() {};
};

