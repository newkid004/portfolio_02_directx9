#include "sceneTest2.h"

#include "managerList.h"
#include "gMng.h"

#include "pickRay.h"

#include "nodeMesh.h"

#include "aStar_node.h"
#include "aStar_grape.h"
#include "aStar_runner.h"
#include "aStar_path.h"

constexpr float INTERVAL = 3.0f;
constexpr float SIZE_BIG = 0.1f;
constexpr float SIZE_LOW = 0.03f;

sceneTest2::~sceneTest2()
{
	SAFE_DELETE(_grape);
	SAFE_DELETE(_pathResult);
}

void sceneTest2::init(void)
{
	sceneBase::init();

	_customMesh = createCustomMesh();
	_grape = createGrape();

	_customMesh->setPlaneRadius(1.0f);
}

void sceneTest2::update(void)
{
	sceneBase::update();

	updateMouse();
	updateKey();
}

void sceneTest2::draw(void)
{
	sceneBase::draw();

	drawMesh();
	drawConnect();
}

void sceneTest2::drawUI(void)
{
	sceneBase::drawUI();
}

void sceneTest2::updateMouse(void)
{
	// 선택 노드 추가
	if (MN_KEY->mousePress())
	{
		auto & nodeList = _grape->getNodeList();
		for (int z = 0; z <= nodeList.size() / 5; ++z)
		{
			for (int x = 0; x < 5; ++x)
			{
				int index = (z * 5) + x;
				if (nodeList.size() <= index)
					return;

				bool isFind = false;
				auto viewNode = (*_grape)[index];
				if (_pathResult != nullptr)
				{
					for (auto i : _pathResult->unpack())
					{
						if (viewNode == i->getMember().placedNode)
						{
							isFind = true;
							break;
						}
					}
				}
				
				aStar_node::info *nodeInfo;
				viewNode->getInfo(nodeInfo);
				_customMesh->setPosition(nodeInfo->pos);

				_customMesh->update();

				pick::ray pRay;
				pick::info pInfo;
				pick::applyMatrix(&pRay, NULL, &_customMesh->getMatrixFinal());
				if (pick::chkPick(&pInfo, &pRay, _customMesh->getMeshSet()->mesh))
					gMng::add(viewNode, _vSelectionNode);
			}
		}
	}
	else if (MN_KEY->mousePress(EMouseInput::RIGHT))
	{
		_vSelectionNode.clear();
	}
	else if (MN_KEY->mousePress(EMouseInput::MIDDLE))
	{
		static int size = 25;
		D3DXVECTOR3 viewPos = D3DXVECTOR3(((size % 5) - 3) * INTERVAL, 1, ((size / 5) - 3) * INTERVAL);
		_grape->addNode(new aStar_node(viewPos));

		++size;
	}
}

void sceneTest2::updateKey(void)
{
	if (MN_KEY->keyPress(DIK_DELETE))
	{
		for (auto i : _vSelectionNode)
			_grape->deleteNode(i);

		_vSelectionNode.clear();
		SAFE_DELETE(_pathResult);
	}
	if (MN_KEY->keyDown(DIK_LSHIFT))
	{
		// connect
		if (MN_KEY->keyPress(DIK_C))
		{
			for (int i = 0; i < _vSelectionNode.size(); ++i)
			{
				for (int j = i + 1; j < _vSelectionNode.size(); ++j)
					_grape->connectNode(_vSelectionNode[i], _vSelectionNode[j]);
			}
		}

		// pathfind
		if (MN_KEY->keyPress(DIK_P))
		{
			if (_vSelectionNode.size() < 2)
				return;

			auto startNode = _vSelectionNode[0];
			auto destNode = _vSelectionNode[1];

			_grape->pathfind(&_pathResult, startNode, destNode);
		}
	}
}

void sceneTest2::drawMesh(void)
{
	auto & nodeList = _grape->getNodeList();
	for (int z = 0; z <= nodeList.size() / 5; ++z)
	{
		for (int x = 0; x < 5; ++x)
		{
			int index = (z * 5) + x;
			if (nodeList.size() <= index)
				return;

			bool isFind = false;
			auto viewNode = (*_grape)[index];
			if (_pathResult != nullptr)
			{
				for (auto i : _pathResult->unpack())
				{
					if (viewNode == i->getMember().placedNode)
					{
						isFind = true;
						break;
					}
				}
			}

			if (isFind)
				_customMesh->setNodeColor(D3DXVECTOR4(1, 0, 0, 1));
			else
				_customMesh->setNodeColor(D3DXVECTOR4(1, 1, 1, 1));

			aStar_node::info *nodeInfo;
			viewNode->getInfo(nodeInfo);
			_customMesh->setPosition(nodeInfo->pos);

			_customMesh->update();
			_customMesh->draw();
		}
	}
}

void sceneTest2::drawConnect(void)
{
	D3DXMATRIXA16 mWorld;
	D3DXMatrixIdentity(&mWorld);
	MN_DEV->SetTransform(D3DTS_WORLD, &mWorld);

	vertex v[2];
	MN_DEV->SetFVF(vertex::FVF);

	auto & nodeList = _grape->getNodeList();
	for (int z = 0; z <= nodeList.size() / 5; ++z)
	{
		for (int x = 0; x < 5; ++x)
		{
			int index = (z * 5) + x;
			if (nodeList.size() <= index)
				return;

			auto viewNode = (*_grape)[index];

			aStar_node::info *nodeInfo; viewNode->getInfo(nodeInfo);
			v[0].pos = nodeInfo->pos;

			for (auto i : viewNode->getLinkedNodeList())
			{
				aStar_node::info *conInfo; i.connector->getInfo(conInfo);
				v[1].pos = conInfo->pos;

				MN_DEV->DrawPrimitiveUP(D3DPT_LINELIST, 1, v, sizeof(vertex));
			}
		}
	}
}

aStar_grape * sceneTest2::createGrape(void)
{
	aStar_grape* result = new aStar_grape();

	for (int z = 0; z < 5; ++z)
	{
		for (int x = 0; x < 5; ++x)
			result->addNode(new aStar_node(D3DXVECTOR3((x - 3) * INTERVAL, 1, (z - 3) * INTERVAL)));
	}

	return result;
}

nodeMesh * sceneTest2::createCustomMesh(void)
{
	nodeMesh::mParam param;
	param.meshFilePath = "resource/mesh/sphere.x";
	param.effectFilePath = "resource/effect/field_node.fx";

	return new nodeMesh(param);
}
