#include "sceneMapTool.h"

#include "managerList.h"

#include "cameraControlable.h"
#include "debugGrid.h"

sceneMapTool::sceneMapTool()
{
	_grid->setVisible(false);
	((cameraControlable*)GET_CAMERA())->setVisible(false);
}

void sceneMapTool::init(void)
{
	sceneBase::init();

	
}

void sceneMapTool::update(void)
{
	sceneBase::update();
}

void sceneMapTool::draw(void)
{
	sceneBase::draw();
}

void sceneMapTool::drawUI(void)
{
	sceneBase::drawUI();
}
