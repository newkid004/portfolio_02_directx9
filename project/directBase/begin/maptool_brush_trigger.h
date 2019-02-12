#pragma once
#include "kGlobalDefine.h"
#include "maptool_brush.h"

class maptool_brush_trigger : public maptool_brush
{
protected:
	virtual void updateKey(void) override;

protected:
	// mouse
	virtual void updateObjectMove(POINT & mouseMove) override;
	virtual void updateObjectRotate(POINT & mouseMove) override {};
	virtual void updateObjectScale(void) override;

	// key
	virtual void updateObjectDelete(void) override;
	virtual void updateConnectNode(void);

	// mouse active
	virtual void putObject(void) override;

public:
	maptool_brush_trigger(sceneMapTool* viewData) : maptool_brush(viewData) {};
	~maptool_brush_trigger() {};
};

