#include "sceneTest2.h"

#include "managerList.h"
#include "gMng.h"

#include "pickRay.h"

#include "staticMesh.h"

#include "aStar_node.h"
#include "aStar_grape.h"
#include "aStar_runner.h"

sceneTest2::~sceneTest2()
{
	SAFE_DELETE(_grape);
}

void sceneTest2::init(void)
{
	sceneBase::init();

	_staticMesh = createStaticMesh();
	_grape = createGrape();
}

void sceneTest2::update(void)
{
	sceneBase::update();

	updateControl();
}

void sceneTest2::draw(void)
{
	sceneBase::draw();

	auto & nodeList = _grape->getNodeList();

	auto viewStack(_pathResult);
	for (int z = 0; z < nodeList.size() / 5; ++z)
	{
		for (int x = 0; x < nodeList.size() % 5; ++x)
		{
			D3DXVECTOR3 viewPos = D3DXVECTOR3((x - 3) * 10, 1, (z - 3) * 10);
			auto viewRunner = viewStack.top();
			auto viewNode = viewRunner.getMember().placedNode;

			if (gMng::find(viewNode, nodeList))
				_staticMesh->setScale(0.5f);
			else
				_staticMesh->setScale(0.2f);
			_staticMesh->setPosition(viewPos);

			_staticMesh->update();

			_staticMesh->draw();
		}
	}
}

void sceneTest2::drawUI(void)
{
	sceneBase::drawUI();
}

void sceneTest2::updateControl(void)
{
	// 선택 노드 추가
	if (MN_KEY->mousePress())
	{
		auto & nodeList = _grape->getNodeList();

		auto viewStack(_pathResult);
		for (int z = 0; z < nodeList.size() / 5; ++z)
		{
			for (int x = 0; x < nodeList.size() % 5; ++x)
			{
				D3DXVECTOR3 viewPos = D3DXVECTOR3((x - 3) * 10, 1, (z - 3) * 10);
				auto viewRunner = viewStack.top();
				auto viewNode = viewRunner.getMember().placedNode;

				if (gMng::find(viewNode, nodeList))
					_staticMesh->setScale(0.5f);
				else
					_staticMesh->setScale(0.2f);
				_staticMesh->setPosition(viewPos);

				_staticMesh->update();

				pick::ray pRay;
				pick::info pInfo;
				pick::applyMatrix(&pRay, NULL, &_staticMesh->getMatrixFinal());
				if (pick::chkPick(&pInfo, &pRay, _staticMesh->getMeshSet()->mesh))
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
		int size = _grape->getNodeList().size();
		D3DXVECTOR3 viewPos = D3DXVECTOR3(((size % 5) - 3) * 10, 1, ((size / 5) - 3) * 10);
		_grape->addNode(new aStar_node(viewPos));
	}
}

aStar_grape * sceneTest2::createGrape(void)
{
	aStar_grape* result = new aStar_grape();

	for (int z = 0; z < 5; ++z)
	{
		for (int x = 0; x < 5; ++x)
			result->addNode(new aStar_node(D3DXVECTOR3((x - 3) * 10, 1, (z - 3) * 10)));
	}

	return result;
}

staticMesh * sceneTest2::createStaticMesh(void)
{
	staticMesh::mParam param;
	param.meshFilePath = "resource/mesh/Elementalist/Elementalist.x";
	param.effectFilePath = "resource/effect/example_16.fx";

	return new staticMesh(param);
}
