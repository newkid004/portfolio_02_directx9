#include "maptool_brush_trigger.h"

#include "managerList.h"

#include "maptool_field.h"
#include "maptool_data_catalog.h"

#include "windowCtlogMaptool.h"

#include "nodeMesh.h"
#include "aStar_grape_bind.h"

void maptool_brush_trigger::updateKey(void)
{
	maptool_brush::updateKey();
	updateConnectNode();
}

void maptool_brush_trigger::updateObjectMove(POINT & mouseMove)
{
	nodeMesh* selection = (nodeMesh*)_set.data_field->getSet().selectionObject;

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

	aStar_node::info* nodeInfo;
	selection->getBindNode()->getInfo(nodeInfo);
	nodeInfo->pos = selection->getPosition();
}

void maptool_brush_trigger::updateObjectScale(void)
{
	nodeMesh* selection = (nodeMesh*)_set.data_field->getSet().selectionObject;

	float scale = selection->getPlaneRadius();

	float ratio = 1.0f;
	if (MN_KEY->keyDown(DIK_LCONTROL))
		ratio *= 0.33f;
	else if (MN_KEY->keyDown(DIK_LSHIFT))
		ratio *= 3.0f;

	if (MN_KEY->wheelUp())
		scale *= std::powf(1.1f, ratio);
	else if (MN_KEY->wheelDown())
		scale *= std::powf(0.9f, ratio);

	selection->setPlaneRadius(scale);
}

void maptool_brush_trigger::updateObjectDelete(void)
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
			_set.data_field->getSet().pathGrape->deleteNode(i);

			selection = nullptr;

			break;
		}
	}
}

void maptool_brush_trigger::updateConnectNode(void)
{
}

void maptool_brush_trigger::putObject(void)
{
	typedef maptool_data_catalog CATALOG;
	typedef CATALOG::OBJ CATA_OBJ;

	windowCtlogMaptool* viewWindow = *_set.bindWindow;

	// 카탈로그 내 아이템정보 복사
	CATA_OBJ::NODE* item = (CATA_OBJ::NODE*)viewWindow->getItem();
	nodeMesh* duplication = nullptr;
	CATALOG::duplicate(&duplication, item);

	if (duplication)
	{
		maptool_data_io::OBJ::NODE* ioBase = nullptr;
		maptool_data_io::create(&ioBase, duplication);

		// 복사한 정보 field내 리스트에 추가
		if (ioBase)
		{
			_set.data_field->getSet().objList.push_back(duplication);
			_set.data_field->getSet().dataList.push_back(ioBase);

			auto & selection = _set.data_field->getSet().selectionObject;
			selection = duplication;

			// 위치, 회전 초기화
			D3DXVECTOR3 pickPos;
			if (pick::chkPick(&pickPos, NULL, &terrain::getDefPlane()))
				selection->setPosition(pickPos);

			// bind 추가
			aStar_node* inputNode = new aStar_node(duplication->getPosition());
			duplication->setBindNode(inputNode);

			nodeMesh** copyTarget = nullptr;
			_set.data_field->getSet().pathGrape->addNode(inputNode, &copyTarget);
			*copyTarget = duplication;
		}
	}
}
