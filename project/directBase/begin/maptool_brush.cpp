#include "maptool_brush.h"

#include "gMng.h"

#include "sceneMapTool.h"

#include "maptool_window.h"
#include "maptool_io.h"
#include "maptool_field.h"

#include "windowCtlogMaptool.h"

#include "nodeMesh.h"

#include "aStar_path.h"

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

		auto & selectionList = _set.data_field->getSet().selectionObject;

		// pick check
		if (MN_KEY->mousePress())
			updatePickObject();

		// release selection
		if (MN_KEY->mousePress(EMouseInput::RIGHT))
		{
			SAFE_DELETE(_set.data_field->getSet().pathData);
			updateReleaseSelection();
		}

		// object control
		if (!selectionList.empty())
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
	_set.data_field->getSet().selectionObject.clear();
	_set.data_field->getSet().selectionData.clear();
}

void maptool_brush::updatePickObject(void)
{
	auto data_field = _set.data_field;

	maptool_field::set::OBJ pickObject = nullptr;
	maptool_field::set::DATA pickData = nullptr;

	data_field->getPickObject(&pickObject, &pickData);

	if (pickObject && !gMng::find(pickObject, data_field->getSet().selectionObject))
	{
		data_field->getSet().selectionObject.push_back(pickObject);
		data_field->getSet().selectionData.push_back(pickData);

		MN_KEY->resetMousePressDb();
	}
}

void maptool_brush::updateObjectRotate(POINT & mouseMove)
{
	auto & selectionList = _set.data_field->getSet().selectionObject;

	for (auto selection : selectionList)
	{
		if (!MN_KEY->keyDown(DIK_SPACE))
			selection->rotateY(-mouseMove.x / 8.0f, false);
		else
		{
			selection->rotateCameraX(-mouseMove.y / 8.0f);
			selection->rotateCameraY(-mouseMove.x / 8.0f);
		}
	}
}

void maptool_brush::updateObjectScale(void)
{
	auto & selectionList = _set.data_field->getSet().selectionObject;

	for (auto selection : selectionList)
	{
		auto selectObject = dynamic_cast<nodeMesh*>(selection);
		if (selectObject == nullptr)	// 선택개체가 nodeMesh가 아닐경우만
		{
			D3DXVECTOR3 scale = selection->getScale();

			float ratio = 1.0f;
			if (MN_KEY->keyDown(DIK_LCONTROL))
				ratio *= 0.01f;
			else if (MN_KEY->keyDown(DIK_LSHIFT))
				ratio *= 3.0f;

			if (MN_KEY->wheelUp())
				scale *= std::powf(1.1f, ratio);
			else if (MN_KEY->wheelDown())
				scale *= std::powf(0.9f, ratio);

			if (MN_KEY->keyPress(DIK_A))
			{
				scale *= 0.0508f;
			}
			selection->setScale(scale);
		}
	}

}

void maptool_brush::updateObjectMove(POINT & mouseMove)
{
	auto & selectionList = _set.data_field->getSet().selectionObject;

	if (MN_KEY->mousePressDb())
	{
		D3DXVECTOR3 pickPos;
		if (pick::chkPick(&pickPos, NULL, &terrain::getDefPlane()))
		{
			for (auto selection : selectionList)
				selection->setPosition(pickPos);
		}
	}
	else
	{
		float dev = 20.0f;

		// x, y
		if (MN_KEY->keyDown(DIK_SPACE))
		{
			for (auto selection : selectionList)
			{
				selection->moveCameraX(mouseMove.x / dev);
				selection->moveCameraY(-mouseMove.y / dev);
			}
		}
		// x, z
		else
		{
			for (auto selection : selectionList)
			{
				selection->moveCameraX(mouseMove.x / dev, true);
				selection->moveCameraZ(-mouseMove.y / dev, true);
			}
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
	if (MN_KEY->keyPress(DIK_DELETE) && !_set.data_field->getSet().selectionObject.empty())
		updateObjectDelete();
}

void maptool_brush::updateWindowClose(void)
{
	(*_set.bindWindow)->getIndex() = -1;
	(*_set.bindWindow)->close();
}

void maptool_brush::updateIO(void)
{
	if (MN_KEY->keyDown(DIK_LCONTROL))
	{
		if (MN_KEY->keyPress(DIK_S))
			_set.data_io->write();

		if (MN_KEY->keyPress(DIK_L))
		{
			int fileSelection = _set.data_window->getSet().mv_file->getIndex();

			_set.data_io->read();

			_set.data_window->getSet().mv_file->getIndex() = fileSelection;
		}
	}
}

void maptool_brush::updateObjectDelete(void)
{
	auto & selectionList = _set.data_field->getSet().selectionObject;

	auto & vObjList = _set.data_field->getSet().objList;
	auto & vDataList = _set.data_field->getSet().dataList;

	for (int i = selectionList.size() - 1; 0 <= i; --i)
	{
		auto & selection = selectionList[i];

		for (int j = 0; j < vObjList.size(); ++j)
		{
			if (vObjList[j] == selection)
			{
				SAFE_DELETE(vObjList[j]);
				SAFE_DELETE(vDataList[j]);

				vObjList.erase(vObjList.begin() + j);
				vDataList.erase(vDataList.begin() + j);

				selectionList.erase(selectionList.begin() + i);

				break;
			}
		}
	}

	SAFE_DELETE(_set.data_field->getSet().pathData);
}
