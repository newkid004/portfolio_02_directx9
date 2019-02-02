#include "sceneMapTool.h"

#include "managerList.h"

#include "cameraControlable.h"
#include "debugGrid.h"

#include "maptool_data_io.h"
#include "maptool_window.h"
#include "maptool_field.h"

#include "windowCtlogMaptool.h"

#include "terrain.h"
#include "staticMesh.h"
#include "pickRay.h"

sceneMapTool::~sceneMapTool()
{
	SAFE_DELETE(_window);
	SAFE_DELETE(_field);
}

void sceneMapTool::init(void)
{
	sceneBase::init();

	_window = new maptool_window();
	_field = new maptool_field();

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

	if (MN_KEY->mouseDown())
	{
		D3DXVECTOR3 pickPos;
		if (pick::chkPick(&pickPos, NULL, &terrain::getDefPlane()))
		{
			_staticMesh->setPosition(pickPos);
		}
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

