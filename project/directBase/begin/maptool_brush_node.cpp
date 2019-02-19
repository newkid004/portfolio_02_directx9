#include "maptool_brush_node.h"

#include "managerList.h"
#include "gMng.h"

#include "maptool_field.h"
#include "maptool_data_catalog.h"

#include "windowCtlogMaptool.h"

#include "nodeMesh.h"
#include "aStar_grape_bind.h"
#include "aStar_path.h"

void maptool_brush_node::updateKey(void)
{
	maptool_brush::updateKey();
	updateConnectNode();
}

void maptool_brush_node::updateObjectMove(POINT & mouseMove)
{
	aStar_node::info* nodeInfo = nullptr;
	auto & selectionList = _set.data_field->getSet().selectionObject;

	if (MN_KEY->mousePressDb())
	{
		D3DXVECTOR3 pickPos;
		if (pick::chkPick(&pickPos, NULL, &terrain::getDefPlane()))
		{
			for (int i = 0; i < selectionList.size(); ++i)
			{
				nodeMesh* selection = dynamic_cast<nodeMesh*>(selectionList[i]);

				if (selection)
				{
					selectionList[i]->setPosition(pickPos);

					selection->getBindNode()->getInfo(nodeInfo);
					nodeInfo->pos = selection->getPosition();
				}
			}
		}
	}
	else
	{
		float dev = 20.0f;

		// x, y
		if (MN_KEY->keyDown(DIK_SPACE))
		{
			for (int i = 0; i < selectionList.size(); ++i)
			{
				nodeMesh* selection = dynamic_cast<nodeMesh*>(selectionList[i]);

				if (selection)
				{
					selectionList[i]->moveCameraX(mouseMove.x / dev);
					selectionList[i]->moveCameraY(-mouseMove.y / dev);

					selection->getBindNode()->getInfo(nodeInfo);
					nodeInfo->pos = selection->getPosition();
				}
			}
		}
		// x, z
		else
		{
			for (int i = 0; i < selectionList.size(); ++i)
			{
				nodeMesh* selection = dynamic_cast<nodeMesh*>(selectionList[i]);

				if (selection)
				{
					selectionList[i]->moveCameraX(mouseMove.x / dev, true);
					selectionList[i]->moveCameraZ(-mouseMove.y / dev, true);

					selection->getBindNode()->getInfo(nodeInfo);
					nodeInfo->pos = selection->getPosition();
				}
			}
		}
	}
}

void maptool_brush_node::updateObjectScale(void)
{
	auto & selectionList = _set.data_field->getSet().selectionObject;

	for (int i = 0; i < selectionList.size(); ++i)
	{
		nodeMesh* selection = dynamic_cast<nodeMesh*>(selectionList[i]);

		if (selection)
		{
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
	}
}

void maptool_brush_node::updateObjectDelete(void)
{
	auto & selectionList = _set.data_field->getSet().selectionObject;

	auto & vObjList = _set.data_field->getSet().objList;
	auto & vDataList = _set.data_field->getSet().dataList;

	for (int i = 0; i < selectionList.size();)
	{
		auto & selection = selectionList[i];

		bool isFind = false;
		for (int j = 0; j < vObjList.size(); ++j)
		{
			if (vObjList[j] == selection)
			{
				auto node = (nodeMesh*)vObjList[j];
				_set.data_field->getSet().pathGrape->deleteNode(node->getBindNode()->getIndex());

				SAFE_DELETE(vObjList[j]);
				SAFE_DELETE(vDataList[j]);

				vObjList.erase(vObjList.begin() + j);
				vDataList.erase(vDataList.begin() + j);

				selectionList.erase(selectionList.begin() + i);
				isFind = true;

				break;
			}
		}
		if (!isFind) ++i;
	}

	SAFE_DELETE(_set.data_field->getSet().pathData);
}

void maptool_brush_node::updateConnectNode(void)
{
	static D3DXVECTOR4 emptyColor = D3DXVECTOR4(1, 1, 1, 1);
	static D3DXVECTOR4 pathColor = D3DXVECTOR4(0.3f, 0.3f, 1, 1);

	auto & selectionList = _set.data_field->getSet().selectionObject;
	auto grape = _set.data_field->getSet().pathGrape;

	// connect
	if (MN_KEY->keyPress(DIK_C))
	{
		auto grape = _set.data_field->getSet().pathGrape;

		for (int i = 0; i < selectionList.size(); ++i)
		{
			auto nodeA = dynamic_cast<nodeMesh*>(selectionList[i]);
			if (nodeA == nullptr) continue;

			for (int j = i + 1; j < selectionList.size(); ++j)
			{
				auto nodeB = dynamic_cast<nodeMesh*>(selectionList[j]);
				if (nodeB == nullptr) continue;

				grape->connectNode(
					nodeA->getBindNode()->getIndex(),
					nodeB->getBindNode()->getIndex());
			}
		}
	}

	// pathfind
	if (MN_KEY->keyPress(DIK_P))
	{
		for (auto i : grape->getNodeList())
			((nodeMesh*)i->getBindData())->setNodeColor(emptyColor);

		if (selectionList.size() < 2)
			return;

		nodeMesh* target[2] = { nullptr, };
		for (auto i : selectionList)
		{
			if (target[0] && target[1])
				break;

			else if (target[0])
				target[1] = dynamic_cast<nodeMesh*>(i);

			else
				target[0] = dynamic_cast<nodeMesh*>(i);
		}

		if (!(target[0] && target[1]))
			return;

		auto & path = _set.data_field->getSet().pathData;
		SAFE_DELETE(path);

		grape->pathfind(&path, target[0]->getBindNode(), target[1]->getBindNode());

		for (auto & i : path->unpack())
			((nodeMesh*)i->getMember().placedNode->getBindData())->setNodeColor(pathColor);
	}
}

void maptool_brush_node::putObject(void)
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

			auto & selectionList = _set.data_field->getSet().selectionObject;

			selectionList.clear();
			selectionList.push_back(duplication);

			auto & selection = selectionList.front();

			// 위치, 회전 초기화
			D3DXVECTOR3 pickPos;
			if (pick::chkPick(&pickPos, NULL, &terrain::getDefPlane()))
				selection->setPosition(pickPos);

			// bind 추가
			aStar_node* inputNode = new aStar_node(duplication->getPosition());
			duplication->setBindNode(inputNode);

			aStar_grape_bind<nodeMesh>::BIND_OUT copyTarget = nullptr;
			_set.data_field->getSet().pathGrape->addNode(inputNode, copyTarget);
			*copyTarget = duplication;
		}
	}
}
