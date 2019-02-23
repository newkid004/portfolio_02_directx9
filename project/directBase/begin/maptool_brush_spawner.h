#pragma once
#include "kGlobalDefine.h"
#include "maptool_brush_node.h"

class maptool_brush_spawner : public maptool_brush_node
{
protected:
	virtual void updateKey(void) override;

protected:
	// mouse
	virtual void updateObjectMove(POINT & mouseMove) override;

	// key
	virtual void updateObjectDelete(void) override;

	// mouse active
	virtual void putObject(void) override;

public:
	maptool_brush_spawner(sceneMapTool* viewData) : maptool_brush_node(viewData) {};
	~maptool_brush_spawner() {};
};

