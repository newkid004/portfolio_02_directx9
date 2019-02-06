#include "sceneMapTool.h"

#include "managerList.h"

#include "cameraControlable.h"
#include "debugGrid.h"

#include "maptool_data_io.h"

#include "maptool_window.h"
#include "maptool_field.h"
#include "maptool_render.h"
#include "maptool_io.h"

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
}

void sceneMapTool::init(void)
{
	sceneBase::init();

	ZeroMemory(&_mousePrev, sizeof(POINT));

	_window	= new maptool_window();
	_field	= new maptool_field(NULL);
	_render	= new maptool_render();
	_io		= new maptool_io(_field);

	// _grid->setVisible(false);
	// ((cameraControlable*)_camera)->setVisible(false);
}

void sceneMapTool::update(void)
{
	MN_UI->update();
	updateControl_Prop();
	updateControl_key();

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
}

void sceneMapTool::updateControl_Prop(void)
{
	if (MN_KEY->getClickIgnore())
		return;

	windowCtlogMaptool* viewWindow = nullptr;
	if (viewWindow = _window->getSet().focusedWindow)
	{
		if (0 <= viewWindow->getIndex())
		{
			// 01. prop put
			if (MN_KEY->mousePress())
			{
				putProp();
				viewWindow->getIndex() = -1;
			}
		}
	}
	if (viewWindow == nullptr || viewWindow->getIndex() < 0)
	{
		// ready to rotate
		if (MN_KEY->keyDown(DIK_LSHIFT) && MN_KEY->mousePress())
			_mousePrev = MN_KEY->getMousePos();

		renderObject* pickObject = nullptr;
		if (MN_KEY->mousePress())
		{
			// 02. pick check
			if (pickObject = _field->getPickObject())
				_field->getSet().selectionObject = pickObject;
		}
		if (MN_KEY->mousePress(EMouseInput::RIGHT))
			_field->getSet().selectionObject = nullptr;

		if (MN_KEY->keyDown(DIK_LCONTROL) && MN_KEY->mouseDown())
		{
			// 03. prop move
			if (_field->getSet().selectionObject != nullptr) // && pickObject != _field->getSet().selectionObject)
			{
				D3DXVECTOR3 pickPos;
				if (pick::chkPick(&pickPos, NULL, &terrain::getDefPlane()))
					_field->getSet().selectionObject->setPosition(pickPos);
			}
		}
		else if (MN_KEY->keyDown(DIK_LSHIFT) && MN_KEY->mouseDown())
		{
			// 04. prop rotate
			if (_field->getSet().selectionObject != nullptr)
			{
				POINT mouseMove = {
					MN_KEY->getMousePos().x - _mousePrev.x,
					MN_KEY->getMousePos().y - _mousePrev.y };

				if (!MN_KEY->keyDown(DIK_SPACE))
					_field->getSet().selectionObject->rotateY(-mouseMove.x / 8.0f, false);
				else
				{
					_field->getSet().selectionObject->rotateCameraX(-mouseMove.y / 8.0f);
					_field->getSet().selectionObject->rotateCameraY(-mouseMove.x / 8.0f);
				}

				MN_KEY->setMousePos(_mousePrev);
			}
		}
	}
}

void sceneMapTool::updateControl_key(void)
{
	// save, load
	if (MN_KEY->keyDown(DIK_LCONTROL) && MN_KEY->keyPress(DIK_S))
		_io->write();
	if (MN_KEY->keyDown(DIK_LCONTROL) && MN_KEY->keyPress(DIK_L))
		_io->read();

	// prop delete
	if (MN_KEY->keyPress(DIK_DELETE) && _field->getSet().selectionObject != nullptr)
	{
		auto & vObjList = _field->getSet().objList;
		auto & vDataList = _field->getSet().dataList;

		auto & selection = _field->getSet().selectionObject;
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
}

void sceneMapTool::putProp(void)
{
	typedef maptool_data_catalog CATALOG;
	typedef CATALOG::OBJ CATA_OBJ;
	
	windowCtlogMaptool* viewWindow = _window->getSet().focusedWindow;
	
	CATA_OBJ::BASE* item = viewWindow->getItem();
	renderObject* duplication = nullptr;

	// 카탈로그 내 아이템정보 복사
	if (item->_baseType & CATALOG::baseType::CHAR)			CATALOG::duplicate((skinnedMesh**)&duplication, (CATA_OBJ::CHAR*)item);
	// else if (item->_baseType & CATALOG::baseType::EVENT)	CATALOG::duplicate((CATA_OBJ::EVENT**)&duplication, (CATA_OBJ::EVENT*)item);
	else if (item->_baseType & CATALOG::baseType::PROP)		CATALOG::duplicate((staticMesh**)&duplication, (CATA_OBJ::PROP*)item);

	if (duplication)
	{
		typedef maptool_data_io DATA_IO;

		DATA_IO::OBJ::BASE* ioBase = nullptr;

		if (item->_baseType & CATALOG::baseType::CHAR)			DATA_IO::create((DATA_IO::OBJ::CHAR**)&ioBase, (skinnedMesh*)duplication);
		// else if (item->_baseType & CATALOG::baseType::EVENT)	DATA_IO::create((DATA_IO::OBJ::EVENT**)&ioBase, (skinnedMesh*)duplicateObject);
		else if (item->_baseType & CATALOG::baseType::PROP)		DATA_IO::create((DATA_IO::OBJ::PROP**)&ioBase, (staticMesh*)duplication);

		// 복사한 정보 field내 리스트에 추가
		if (ioBase)
		{
			_field->getSet().objList.push_back(duplication);
			_field->getSet().dataList.push_back(ioBase);

			_field->getSet().selectionObject = duplication;

			// 위치, 회전 초기화
			D3DXVECTOR3 pickPos;
			if (pick::chkPick(&pickPos, NULL, &terrain::getDefPlane()))
				_field->getSet().selectionObject->setPosition(pickPos);

			_field->getSet().selectionObject->rotateBillboard(true, true);
		}
	}
}
