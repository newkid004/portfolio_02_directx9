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
#include "inGame_field.h"

#include "characterBase.h"
#include "player.h"

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
	updatePlace();			// 현재 노드를 업데이트
	updatePath();			// 길찾기 계산(플레이어를 향한)
	updateFootPrint();		// 지나온 노드를 지운다
}

void controllerBase::updatePlace(void)
{
	auto & grape = SGT_GAME->getSet().field->getMember().grape;
	auto & pNode = _bindCharacter->getPlacedNode();
	auto & iNode = grape->getBindList()[pNode->getIndex()];
	
	D3DXVECTOR2 placedPos = D3DXVECTOR2(_bindCharacter->getPosition().x, _bindCharacter->getPosition().z);
	float placedRadius = _bindCharacter->getInfoCharacter().colRadius;

	D3DXVECTOR2 nodePos = D3DXVECTOR2(iNode->getPosition().x, iNode->getPosition().z);
	float nodeRadius = iNode->getRadius();

	// 노드 범위 벗어남
	if (gFunc::Vec2Distance(placedPos, nodePos) < placedRadius + nodeRadius)
	{
		for (auto & i : pNode->getLinkedNodeList())
		{
			auto linkInfo = grape->getBindList()[i.connector->getIndex()];

			D3DXVECTOR2 linkPos = D3DXVECTOR2(linkInfo->getPosition().x, linkInfo->getPosition().z);
			float linkRadius = linkInfo->getRadius();

			if (placedRadius + linkRadius < gFunc::Vec2Distance(placedPos, linkPos))
			{
				_bindCharacter->getPlacedNode() = i.connector;
				break;
			}
		}
	}
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

	D3DXVECTOR3 position = _bindCharacter->getPosition();
	position.y = 0.0f;

	auto & placedNode = _bindCharacter->getPlacedNode();
	
	auto & viewData = pathNodeList.front()->getMember();
	auto ownData = inGame_node::getData(viewData.placedNode);
	float ownDistance = gFunc::Vec3Distance(position, ownData->getPosition());

	auto nextData = inGame_node::getData(viewData.nextNode);
	float nextDistance = gFunc::Vec3Distance(position, nextData->getPosition());

	// 위치중인 노드를 벗어나거나, 다음 노드의 범위 들어감
	if (ownData->getRadius() < ownDistance ||
		nextDistance < nextData->getRadius())
	{
		// path 진행
		_path->advance();
		placedNode = pathNodeList.front()->getMember().placedNode;
	}
}

void controllerBase::createPath2Player(void)
{
	SAFE_DELETE(_path);

	auto playerNode = SGT_GAME->getSet().player->getPlacedNode();
	auto placedNode = _bindCharacter->getPlacedNode();

	SGT_GAME->getSet().field->getMember().grape->pathfind(&_path, placedNode, playerNode);
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
	SGT_GAME->getSet().field->getMember().grape->pathfind(&path, placedNode, playerNode);

	// 그래도 못찾음
	if (path == nullptr)
		SAFE_DELETE(_path);

	// 찾음 : 연결
	_path->connect(path, true, true);
}
