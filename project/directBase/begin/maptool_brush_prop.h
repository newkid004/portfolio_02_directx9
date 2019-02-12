#pragma once
#include "kGlobalDefine.h"
#include "maptool_brush.h"

class maptool_brush_prop : public maptool_brush
{
protected :
	virtual void putObject(void);

public:
	maptool_brush_prop(sceneMapTool* viewData);
	~maptool_brush_prop() {};
};

