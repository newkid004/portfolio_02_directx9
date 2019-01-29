#include "sceneMapTool.h"

#include "managerList.h"

#include "cameraControlable.h"
#include "debugGrid.h"

#include "maptool_data.h"
#include "maptool_window.h"

void sceneMapTool::init(void)
{
	sceneBase::init();

	_grid->setVisible(false);
	((cameraControlable*)_camera)->setVisible(false);


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
