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
	_set.data_field->getSet().selectionData = nullptr;
}

void maptool_brush::updatePickObject(void)
{
	auto data_field = _set.data_field;

	auto & pickData = data_field->getSet().selectionData;
	baseObject* & pickObject = data_field->getSet().selectionObject;

	data_field->getPickObject(&pickObject, &pickData);
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

	float ratio = 1.0f;
	if (MN_KEY->keyDown(DIK_LCONTROL))
		ratio *= 0.33f;
	else if (MN_KEY->keyDown(DIK_LSHIFT))
		ratio *= 3.0f;

	if (MN_KEY->wheelUp())
		scale *= std::powf(1.1f, ratio);
	else if (MN_KEY->wheelDown())
		scale *= std::powf(0.9f, ratio);

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
		float dev = 20.0f;

		// x, y
		if (MN_KEY->keyDown(DIK_SPACE))
		{
			selection->moveCameraX(mouseMove.x / dev);
			selection->moveCameraY(-mouseMove.y / dev);
		}
		// x, z
		else
		{
			selection->moveCameraX(mouseMove.x / dev, true);
			selection->moveCameraZ(-mouseMove.y / dev, true);
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
			SAFE_DELETE(vObjList[i]);
			SAFE_DELETE(vDataList[i]);

			vObjList.erase(vObjList.begin() + i);
			vDataList.erase(vDataList.begin() + i);

			selection = nullptr;

			break;
		}
	}
}
