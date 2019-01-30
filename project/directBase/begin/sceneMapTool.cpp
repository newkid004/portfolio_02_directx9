#include "sceneMapTool.h"

#include "managerList.h"

#include "cameraControlable.h"
#include "debugGrid.h"

#include "maptool_data.h"
#include "maptool_window.h"

#include "windowMoveable.h"

sceneMapTool::~sceneMapTool()
{
	SAFE_DELETE(_window);
}

void sceneMapTool::init(void)
{
	sceneBase::init();

	_window = new maptool_window();

	// _grid->setVisible(false);
	// ((cameraControlable*)_camera)->setVisible(false);
}

void sceneMapTool::update(void)
{
	updateControl();
	MN_UI->update();

	sceneBase::update();
}

void sceneMapTool::draw(void)
{
	sceneBase::draw();

}

void sceneMapTool::drawUI(void)
{
	sceneBase::drawUI();

	MN_UI->drawUI();
}

void sceneMapTool::updateControl(void)
{
	if (MN_KEY->keyPress(DIK_P)) 
		MN_UI->find("test")->trans();
}

