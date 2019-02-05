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
	_field = new maptool_field(NULL);

	// _grid->setVisible(false);
	// ((cameraControlable*)_camera)->setVisible(false);
}

void sceneMapTool::update(void)
{
	updateControl_Prop();
	MN_UI->update();

	sceneBase::update();

	_window->update();
	_field->update();
}

void sceneMapTool::draw(void)
{
	sceneBase::draw();

	_field->draw();
}

void sceneMapTool::drawUI(void)
{
	sceneBase::drawUI();

	MN_UI->drawUI();	// window
}

void sceneMapTool::updateControl_Prop(void)
{
	if (windowCtlogMaptool* viewWindow = _window->getSet().focusedWindow)
	{
		if (0 <= viewWindow->getItem() && !MN_KEY->getClickIgnore())
		{
			if (MN_KEY->mousePress())
			{
				// pick check
				if (renderObject* pickObject = _field->getPickObject())
				{
					_field->getSet().selectionObject = pickObject;
				}
			}


			// prop move
			if (auto selection = _field->getSet().selectionObject)
			{
				if (MN_KEY->mouseDown())
				{
					D3DXVECTOR3 pickPos;
					if (pick::chkPick(&pickPos, NULL, &terrain::getDefPlane()))
					{
						selection->setPosition(pickPos);
					}
				}
			}
			// prop put
			else
			{

			}
		}
	}
}
