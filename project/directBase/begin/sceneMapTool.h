#pragma once
#include "kGlobalDefine.h"
#include "sceneBase.h"

class maptool_data;
class maptool_window;
class maptool_field;

class staticMesh;

class sceneMapTool : public sceneBase
{
private :
	maptool_window* _window = nullptr;
	maptool_field* _field = nullptr;

	staticMesh* _staticMesh;

public:
	virtual void init(void) override;
	virtual void update(void) override;
	virtual void draw(void) override;
	virtual void drawUI(void) override;

private :
	void updateControl(void);
	
private :
	staticMesh* createStaticMesh(void);

public:
	sceneMapTool() {};
	~sceneMapTool();
};

