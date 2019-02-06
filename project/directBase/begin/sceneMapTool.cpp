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
	MN_UI->update();
	updateControl_Prop();

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
	if (MN_KEY->getClickIgnore())
	{
		_field->getSet().selectionObject = nullptr;
		return;
	}
	windowCtlogMaptool* viewWindow = nullptr;
	if (viewWindow = _window->getSet().focusedWindow)
	{
		if (0 <= viewWindow->getIndex())
		{
			// 01. prop put
			if (MN_KEY->mousePress())
			{
				typedef maptool_data_catalog CATALOG;
				typedef CATALOG::OBJ CATA_OBJ;

				CATA_OBJ::BASE* item = viewWindow->getItem();
				CATA_OBJ::BASE* duplication = nullptr;

				if (item->_baseType & CATALOG::baseType::CHAR)			CATALOG::duplicate((CATA_OBJ::CHAR**)&duplication, (CATA_OBJ::CHAR*)item);
				else if (item->_baseType & CATALOG::baseType::EVENT)	CATALOG::duplicate((CATA_OBJ::EVENT**)&duplication, (CATA_OBJ::EVENT*)item);
				else if (item->_baseType & CATALOG::baseType::PROP)		CATALOG::duplicate((CATA_OBJ::PROP**)&duplication, (CATA_OBJ::PROP*)item);

				if (duplication)
				{
					typedef maptool_data_io DATA_IO;
					
					auto duplicateObject = ((CATALOG::OBJ::PROP*)duplication)->_object;
					DATA_IO::OBJ::BASE* ioBase = nullptr;

					if (item->_baseType & CATALOG::baseType::CHAR)			DATA_IO::create((DATA_IO::OBJ::CHAR**)&ioBase, (skinnedMesh*)duplicateObject);
					// else if (item->_baseType & CATALOG::baseType::EVENT)	DATA_IO::create((DATA_IO::OBJ::EVENT**)&ioBase, (skinnedMesh*)duplicateObject);
					else if (item->_baseType & CATALOG::baseType::PROP)		DATA_IO::create((DATA_IO::OBJ::PROP**)&ioBase, (staticMesh*)duplicateObject);

					if (ioBase)
					{
						_field->getSet().objList.push_back(duplicateObject);
						_field->getSet().dataList.push_back(ioBase);

						_field->getSet().selectionObject = duplicateObject;
					}
				}
				viewWindow->getIndex() = -1;
			}
		}
	}
	if (viewWindow == nullptr || viewWindow->getIndex() < 0)
	{
		renderObject* pickObject = nullptr;
		if (MN_KEY->mousePress())
		{
			// 02. pick check
			if (pickObject = _field->getPickObject())
				_field->getSet().selectionObject = pickObject;
		}
		if (MN_KEY->mousePress(EMouseInput::RIGHT))
			_field->getSet().selectionObject = nullptr;

		// 03. prop move
		if (MN_KEY->mouseDown() && MN_KEY->keyDown(DIK_LCONTROL))
		{
			if (_field->getSet().selectionObject != nullptr && pickObject != _field->getSet().selectionObject)
			{
				D3DXVECTOR3 pickPos;
				if (pick::chkPick(&pickPos, NULL, &terrain::getDefPlane()))
					_field->getSet().selectionObject->setPosition(pickPos);
			}
		}
	}
}
