#pragma once
#include "kGlobalDefine.h"
#include "maptool_brush.h"

class maptool_brush_trigger : public maptool_brush
{
protected:
	virtual void putObject(void) {};

public:
	maptool_brush_trigger(sceneMapTool* viewData);
	~maptool_brush_trigger() {};
};

