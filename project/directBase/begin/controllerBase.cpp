#include "controllerBase.h"

#include "managerList.h"
#include "gFunc.h"	
#include "gMng.h"

#include "heap.h"

#include "eventDef.h"

#include "aStar_node.h"
#include "aStar_path.h"
#include "inGame_grape.h"
#include "inGame_node.h"

#include "characterBase.h"
#include "player.h"

bool controllerBase::heapCompare::operator()(aStar_node * n1, aStar_node * n2)
{
	auto & vBindList = SGT_GAME->getSet().grape->getBindList();
	inGame_node* infoA = vBindList[n1->getIndex()];
	inGame_node* infoB = vBindList[n1->getIndex()];

	D3DXVECTOR3 & playerPos = SGT_GAME->getSet().player->getPosition();

	float distanceA = gFunc::Vec3Distance(infoA->getPosition(), playerPos);
	float distanceB = gFunc::Vec3Distance(infoB->getPosition(), playerPos);

	return distanceA < distanceB;
}

controllerBase::controllerBase(characterBase* bindCharacter) :
	_bindCharacter(bindCharacter)
{
	_bindCharacter->setController(this);
}

controllerBase::~controllerBase()
{
	SAFE_DELETE(_path);
}

void controllerBase::update(void)
{
	updatePath();
	updateFootPrint();
	updateCollision();

}

void controllerBase::updatePath(void)
{
	if (_path == nullptr)
		createPath2Player();

	else
	{
		auto pNode = SGT_GAME->getSet().player->getPlacedNode();

		// 갱신 불필요 : 도착지가 플레이어 노드와 같음
		if (_path->unpack().back()->getMember().placedNode == pNode)
			return;

		findPath2Player();
	}
}

void controllerBase::updateFootPrint(void)
{
	if (_path == nullptr)
		return;

	auto & pathNodeList = _path->unpack();
	auto playerNode = SGT_GAME->getSet().player->getPlacedNode();

	// 길이 없거나, 플레이어와 같은 위치면 확인 불필요
	if (pathNodeList.size() <= 1 || pathNodeList.front()->getMember().placedNode == playerNode)
		return;

	auto & position = _bindCharacter->getPosition();

	auto & placedNode = _bindCharacter->getPlacedNode();
	auto placedData = inGame_node::getData(placedNode);
	float placedDistance = gFunc::Vec3Distance(position, placedData->getPosition());

	// 현재 노드의 범위 벗어남
	if (placedDistance < placedData->getRadius())
	{
		auto nextNode = pathNodeList.front()->getMember().nextNode;
		auto nextData = inGame_node::getData(nextNode);
		float nextDistance = gFunc::Vec3Distance(position, nextData->getPosition());

		// 다음 노드의 범위 들어감
		if (nextData->getRadius() < nextDistance)
		{
			// path 진행
			_path->advance();
			placedNode = pathNodeList.front()->getMember().placedNode;

			return;
		}
	}
}

void controllerBase::updateCollision(void)
{
	vector<aStar_node*> vColNodeList;
	createCollisionNode(&vColNodeList);

	auto & vBindList = *SGT_GAME->getSet().grape;
	vector<staticMesh*> closeList(vColNodeList.size() * 2);
	for (auto i : vColNodeList)
	{
		auto & wallList = vBindList[i]->getListSet().wall;
		for (auto wall : wallList)
		{
			if (!gMng::find(wall, closeList))
			{
				// 충돌처리 코드 입력
			}
			else
				closeList.push_back(wall);
		}
	}
}

void controllerBase::createPath2Player(void)
{
	SAFE_DELETE(_path);

	auto playerNode = SGT_GAME->getSet().player->getPlacedNode();
	auto placedNode = _bindCharacter->getPlacedNode();

	SGT_GAME->getSet().grape->pathfind(&_path, placedNode, playerNode);
}

void controllerBase::findPath2Player(void)
{
	auto playerNode = SGT_GAME->getSet().player->getPlacedNode();
	
	auto & pathList = _path->unpack();

	// player move to near
	if (pathList.back()->getMember().prevNode == playerNode)
	{
		_path->cutTail();
		return;
	}
	// player move to far
	else
	{
		for (auto i : pathList)
		{
			auto viewNode = i->getMember().placedNode;
			if (viewNode == playerNode)
			{
				_path->putTail(viewNode);
				return;
			}
		}
	}

	// 탐색 : 못찾음
	aStar_path* path = nullptr;
	auto placedNode = _bindCharacter->getPlacedNode();
	SGT_GAME->getSet().grape->pathfind(&path, placedNode, playerNode);

	// 그래도 못찾음
	if (path == nullptr)
		SAFE_DELETE(_path);

	// 찾음 : 연결
	_path->connect(path, true, true);
}

void controllerBase::createCollisionNode(std::vector<aStar_node*> * out_list)
{
	D3DXVECTOR3 & charPos = _bindCharacter->getPosition();
	float charRange = _bindCharacter->getInfoCharacter().colRadian;

	auto & vBindList = *SGT_GAME->getSet().grape;

	heap<aStar_node*, heapCompare> openList;
	vector<aStar_node*> closeList;

	openList.push(_bindCharacter->getPlacedNode());
	while (!openList.empty())
	{
		aStar_node* currentNode = openList.top();

		openList.pop();
		out_list->push_back(currentNode);
		closeList.push_back(currentNode);

		for (auto & i : currentNode->getLinkedNodeList())
		{
			auto linkedNode = i.connector;

			auto bindData = vBindList[linkedNode];
			float distance = gFunc::Vec3Distance(bindData->getPosition(), charPos);
			if (charRange + bindData->getRadius() < distance)
				continue;

			if (gMng::find(linkedNode, closeList))
				continue;

			if (!gMng::find(linkedNode, openList.getContainer()))
				openList.push(linkedNode);
		}
	}
}
