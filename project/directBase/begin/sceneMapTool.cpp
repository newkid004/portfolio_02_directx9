#include "sceneMapTool.h"

#include "managerList.h"

#include "cameraControlable.h"
#include "debugGrid.h"

#include "maptool_data_io.h"
#include "maptool_window.h"

#include "windowCtlogMaptool.h"

#include "staticMesh.h"

sceneMapTool::~sceneMapTool()
{
	SAFE_DELETE(_window);
}

void sceneMapTool::init(void)
{
	sceneBase::init();

	_window = new maptool_window();

	_staticMesh = createStaticMesh();

	// _grid->setVisible(false);
	// ((cameraControlable*)_camera)->setVisible(false);
}

void sceneMapTool::update(void)
{
	updateControl();
	MN_UI->update();

	sceneBase::update();

	_staticMesh->update();
}

void sceneMapTool::draw(void)
{
	sceneBase::draw();

	_staticMesh->draw();
}

void sceneMapTool::drawUI(void)
{
	sceneBase::drawUI();

	MN_UI->drawUI();
}

void sceneMapTool::updateControl(void)
{
	if (MN_KEY->keyPress(DIK_P))
	{
		auto i = new maptool_data_catalog::OBJ::BASE();
		i->_standImage = MN_SRC->getSpriteTexture("resource/texture/practice_05.png");
		_window->getSet().mv_prop->addItem(i);
	}
}

staticMesh * sceneMapTool::createStaticMesh(void)
{
	staticMesh::mParam param = {
		"resource/mesh/Elementalist/Elementalist.x",
		"resource/effect/example_15.fx"
	};

	return new staticMesh(param);
}

