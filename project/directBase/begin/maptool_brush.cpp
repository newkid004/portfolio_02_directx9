#include "maptool_brush.h"

#include "sceneMapTool.h"

#include "maptool_window.h"
#include "maptool_io.h"

#include "windowCtlogMaptool.h"
#include "maptool_field.h"

POINT maptool_brush::_mousePrev = { 0, };

maptool_brush::maptool_brush(sceneMapTool* viewData)
{
	_set.bindWindow = &viewData->_window->getSet().focusedWindow;
	
	_set.data_window	= viewData->_window;
	_set.data_field		= viewData->_field;
	_set.data_io		= viewData->_io;
}

void maptool_brush::update(void)
{
	if (!MN_KEY->getClickIgnore())
		updateMouse();

	updateKey();
}

void maptool_brush::updateMouse(void)
{
	windowCtlogMaptool* focusedWindow = *_set.bindWindow;

	// window open
	if (focusedWindow)
	{
		if (0 <= focusedWindow->getIndex())
		{
			// 01. prop put
			if (MN_KEY->mousePress())
			{
				putObject();
				focusedWindow->getIndex() = -1;
			}
		}
	}

	// window close
	if (focusedWindow == nullptr || focusedWindow->getIndex() < 0)
	{
		// ready to mouse
		if (MN_KEY->mousePress())
			_mousePrev = MN_KEY->getMousePos();

		renderObject* pickObject = nullptr;
		baseObject* & selection = _set.data_field->getSet().selectionObject;

		// pick check
		if (MN_KEY->mousePress())
			updatePickObject();

		// release selection
		if (MN_KEY->mousePress(EMouseInput::RIGHT) &&
			_set.data_window->getSet().focusedWindow != _set.data_window->getSet().mv_file)
			updateReleaseSelection();

		// object control
		if (selection != nullptr)
		{
			if (MN_KEY->mouseDown())
			{
				POINT mouseMove = {
					MN_KEY->getMousePos().x - _mousePrev.x,
					MN_KEY->getMousePos().y - _mousePrev.y };

				// object move
				if (MN_KEY->keyDown(DIK_LCONTROL))
					updateObjectMove(mouseMove);

				// object rotate
				else if (MN_KEY->keyDown(DIK_LSHIFT))
					updateObjectRotate(mouseMove);

				MN_KEY->setMousePos(_mousePrev);
			}

			// object scaling
			if (MN_KEY->wheel())
				updateObjectScale();
		}
	}
}

void maptool_brush::updateReleaseSelection(void)
{
	_set.data_field->getSet().selectionObject = nullptr;
}

void maptool_brush::updatePickObject(void)
{
	if (renderObject* pickObject = _set.data_field->getPickObject())
		_set.data_field->getSet().selectionObject = pickObject;
}

void maptool_brush::updateObjectRotate(POINT & mouseMove)
{
	baseObject* & selection = _set.data_field->getSet().selectionObject;

	if (!MN_KEY->keyDown(DIK_SPACE))
		selection->rotateY(-mouseMove.x / 8.0f, false);
	else
	{
		selection->rotateCameraX(-mouseMove.y / 8.0f);
		selection->rotateCameraY(-mouseMove.x / 8.0f);
	}
}

void maptool_brush::updateObjectScale(void)
{
	baseObject* & selection = _set.data_field->getSet().selectionObject;
	
	D3DXVECTOR3 scale = selection->getScale();

	if (MN_KEY->wheelUp())
		scale *= 1.1f;
	else if (MN_KEY->wheelDown())
		scale *= 0.9f;

	selection->setScale(scale);
}

void maptool_brush::updateObjectMove(POINT & mouseMove)
{
	baseObject* & selection = _set.data_field->getSet().selectionObject;

	if (MN_KEY->mousePressDb())
	{
		D3DXVECTOR3 pickPos;
		if (pick::chkPick(&pickPos, NULL, &terrain::getDefPlane()))
			selection->setPosition(pickPos);
	}
	else
	{
		// x, z
		if (MN_KEY->keyDown(DIK_SPACE))
		{
			selection->moveCameraX(mouseMove.x / 3.0f, true);
			selection->moveCameraZ(-mouseMove.y / 3.0f, true);
		}
		// x, y
		else
		{
			selection->moveCameraX(mouseMove.x / 3.0f, true);
			selection->moveCameraY(-mouseMove.y / 3.0f);
		}
	}
}

void maptool_brush::updateKey(void)
{
	// window close
	if (MN_KEY->keyPress(DIK_ESCAPE))
		updateWindowClose();

	// save, load
	updateIO();

	// object delete
	if (MN_KEY->keyPress(DIK_DELETE) && _set.data_field->getSet().selectionObject != nullptr)
		updateObjectDelete();
}

void maptool_brush::updateWindowClose(void)
{
	(*_set.bindWindow)->getIndex() = -1;
	(*_set.bindWindow)->close();
}

void maptool_brush::updateIO(void)
{
	if (MN_KEY->keyDown(DIK_LCONTROL) && MN_KEY->keyPress(DIK_S))
		_set.data_io->write();
	if (MN_KEY->keyDown(DIK_LCONTROL) && MN_KEY->keyPress(DIK_L))
	{
		int fileSelection = _set.data_window->getSet().mv_file->getIndex();

		_set.data_io->read();

		_set.data_window->getSet().mv_file->getIndex() = fileSelection;
	}
}

void maptool_brush::updateObjectDelete(void)
{
	auto & selection = _set.data_field->getSet().selectionObject;

	auto & vObjList = _set.data_field->getSet().objList;
	auto & vDataList = _set.data_field->getSet().dataList;

	for (int i = 0; i < vObjList.size(); ++i)
	{
		if (vObjList[i] == selection)
		{
			vObjList.erase(vObjList.begin() + i);
			vDataList.erase(vDataList.begin() + i);

			selection = nullptr;

			break;
		}
	}
}
