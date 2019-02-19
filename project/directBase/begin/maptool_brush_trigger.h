#pragma once
#include "kGlobalDefine.h"
#include "maptool_brush_prop.h"

class maptool_brush_trigger : public maptool_brush_prop
{
public :
	virtual void putObject(void) override;

public:
	maptool_brush_trigger(sceneMapTool* viewData) : maptool_brush_prop(viewData) {};
	~maptool_brush_trigger() {};
};

