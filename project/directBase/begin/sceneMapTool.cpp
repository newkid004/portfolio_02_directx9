#include "sceneMapTool.h"

#include "managerList.h"

#include "cameraControlable.h"
#include "debugGrid.h"

#include "maptool_data_io.h"

#include "maptool_window.h"
#include "maptool_field.h"
#include "maptool_render.h"
#include "maptool_io.h"

#include "maptool_brush.h"
#include "maptool_brush_prop.h"

#include "mapObject.h"

#include "windowCtlogMaptool.h"

#include "terrain.h"
#include "staticMesh.h"
#include "skinnedMesh.h"
#include "pickRay.h"

sceneMapTool::~sceneMapTool()
{
	SAFE_DELETE(_window);
	SAFE_DELETE(_field);
	SAFE_DELETE(_render);
	SAFE_DELETE(_io);

	SAFE_DELETE(_mapObject);
}

void sceneMapTool::init(void)
{
	sceneBase::init();

	ZeroMemory(&_mousePrev, sizeof(POINT));

	// _mapObject = new mapObject();
	// _mapObject->init();

	_window	= new maptool_window();
	_field	= new maptool_field(_mapObject);
	_render	= new maptool_render();
	_io		= new maptool_io(_field, &_window->getSet().mv_file->getIndex());

	_mBrush.insert(decltype(_mBrush)::value_type("prop", new maptool_brush_prop(this)));

	_currentBrush = _mBrush.find("prop")->second;

	// _grid->setVisible(false);
	// ((cameraControlable*)_camera)->setVisible(false);
}

void sceneMapTool::update(void)
{
	MN_UI->update();
	updateControl_brush();

	sceneBase::update();

	_window->update();
	_field->update();
}

void sceneMapTool::draw(void)
{
	// selection outline
	baseObject*& selection = _field->getSet().selectionObject;
	if (selection)
	{
		if (staticMesh* obj = dynamic_cast<staticMesh*>(selection))
		{
			if (!obj->isCull())
				_render->drawOutLine(obj);
		}
	}

	_field->draw();

	sceneBase::draw();
}

void sceneMapTool::drawUI(void)
{
	sceneBase::drawUI();

	MN_UI->drawUI();	// window

	char text[MAX_PATH] = "";
	sprintf(text, "open file window and,\nsave : Ctrl + S\nload : Ctrl + L");
	gFunc::drawText(0, 100, string(text));
}

void sceneMapTool::initMap(void)
{
}

void sceneMapTool::updateControl_brush(void)
{
	int focusWindow = 0;
	windowCtlogMaptool** viewWindow = ((windowCtlogMaptool**)&_window->getSet()) + 3;

	for (int i = 0; i < 4; ++i)
	{
		if (viewWindow + i == &_window->getSet().focusedWindow)
			focusWindow |= 1 << i;
	}

	if (focusWindow & 0b0100)
		_currentBrush = _mBrush.find("trigger")->second;
	else if (focusWindow & 0b1011)
		_currentBrush  = _mBrush.find("prop")->second;

	_currentBrush->update();

}