#pragma once
#include "kGlobalDefine.h"
#include "sceneBase.h"

class sceneMapTool : public sceneBase
{
public:
	virtual void init(void) override;
	virtual void update(void) override;
	virtual void draw(void) override;
	virtual void drawUI(void) override;

public:
	sceneMapTool();
	~sceneMapTool() {};
};

