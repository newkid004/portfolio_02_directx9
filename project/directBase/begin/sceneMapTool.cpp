#include "sceneMapTool.h"

#include "managerList.h"

#include "cameraControlable.h"
#include "debugGrid.h"

#include "maptool_data_io.h"

#include "maptool_window.h"
#include "maptool_field.h"
#include "maptool_render.h"
#include "maptool_io.h"

#include "maptool_brush_prop.h"
#include "maptool_brush_node.h"
#include "maptool_brush_trigger.h"

#include "mapObject.h"

#include "windowCtlogMaptool.h"

#include "terrain.h"
#include "staticMesh.h"
#include "skinnedMesh.h"
#include "pickRay.h"
#include "lightBase.h"
#include "skyBox.h"

sceneMapTool::~sceneMapTool()
{
	SAFE_DELETE(_window);
	SAFE_DELETE(_field);
	SAFE_DELETE(_render);
	SAFE_DELETE(_io);

	SAFE_DELETE(_mapObject);
	SAFE_DELETE(_skybox);
}

void sceneMapTool::init(void)
{
	sceneBase::init();

	ZeroMemory(&_mousePrev, sizeof(POINT));

	//_mapObject = new mapObject();
	//_mapObject->init();

	_window	= new maptool_window();
	_field	= new maptool_field(_mapObject);
	_render	= new maptool_render();
	_io		= new maptool_io(_field, &_window->getSet().mv_file->getIndex());

	_mBrush.insert(decltype(_mBrush)::value_type("prop", new maptool_brush_prop(this)));
	_mBrush.insert(decltype(_mBrush)::value_type("node", new maptool_brush_node(this)));
	_mBrush.insert(decltype(_mBrush)::value_type("trigger", new maptool_brush_trigger(this)));

	_currentBrush = _mBrush.find("prop")->second;

	_skybox = createSkyBox();
	_skybox->setScale(D3DXVECTOR3(10.0f, 10.0f, 10.0f));
	//_skybox->setScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	// _grid->setVisible(false);
	// ((cameraControlable*)_camera)->setVisible(false);
}

void sceneMapTool::update(void)
{
	if (MN_KEY->mouseDown())
		int a = 0;

	MN_UI->update();
	updateControl_brush();

	sceneBase::update();

	_window->update();
	_field->update();
	//_skybox->update();
}

void sceneMapTool::draw(void)
{
	sceneBase::draw();

	drawSelection();

	_field->draw();

	//_skybox->draw();
}

void sceneMapTool::drawUI(void)
{
	sceneBase::drawUI();

	MN_UI->drawUI();	// window

	char text[MAX_PATH] = "";
	sprintf(text, "open file window and,\nsave : Ctrl + S\nload : Ctrl + L");
	gFunc::drawText(0, 100, string(text), COLOR_WHITE(255));
}

void sceneMapTool::initMap(void)
{
}

void sceneMapTool::updateControl_brush(void)
{
	// selection
	if (auto viewData = _field->getSet().getLastData())
	{
		typedef maptool_data_io::baseType TYPE;

		if (viewData->_baseType & TYPE::NODE)
			_currentBrush = _mBrush.find("node")->second;

		else if (viewData->_baseType & TYPE::TRIGGER)
			_currentBrush = _mBrush.find("trigger")->second;

		else if (viewData->_baseType & TYPE::PROP | TYPE::BUMP)
			_currentBrush = _mBrush.find("prop")->second;
	}
	// window
	else if (_window->getSet().focusedWindow && 0 <= _window->getSet().focusedWindow->getIndex())
	{
		if (auto viewData = _window->getSet().focusedWindow->getItem())
		{
			typedef maptool_data_catalog::baseType TYPE;
			
			if (viewData->_baseType & TYPE::NODE)
				_currentBrush = _mBrush.find("node")->second;

			else if (viewData->_baseType & TYPE::TRIGGER)
				_currentBrush = _mBrush.find("trigger")->second;

			else if (viewData->_baseType & TYPE::PROP | TYPE::BUMP)
				_currentBrush = _mBrush.find("prop")->second;
		}
	}

	_currentBrush->update();
}

void sceneMapTool::drawSelection(void)
{
	auto & selectionList = _field->getSet().selectionObject;
	if (!selectionList.empty())
		_render->drawOutList(selectionList);
}

skyBox * sceneMapTool::createSkyBox(void)
{
	skyBox::mParam stParameters = {
		"resource/effect/skySphere.fx",
		"resource/texture/skybox/sky2.png"
	};

	auto pSkybox = new skyBox(stParameters);
	//pSkybox->setScale(D3DXVECTOR3(3000.0f, 3000.0f, 3000.0f));


	
	return pSkybox;
}
