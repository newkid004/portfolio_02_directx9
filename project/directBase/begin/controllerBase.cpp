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
	updatePath();
	updateFootPrint();
}

void controllerBase::updatePath(void)
{
	if (_path == nullptr)
		createPath2Player();

	else
	{
		auto pNode = SGT_GAME->getSet().player->getPlacedNode();

		// ���� ���ʿ� : �������� �÷��̾� ���� ����
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

	// ���� ���ų�, �÷��̾�� ���� ��ġ�� Ȯ�� ���ʿ�
	if (pathNodeList.size() <= 1 || pathNodeList.front()->getMember().placedNode == playerNode)
		return;

	auto & position = _bindCharacter->getPosition();

	auto & placedNode = _bindCharacter->getPlacedNode();
	auto placedData = inGame_node::getData(placedNode);
	float placedDistance = gFunc::Vec3Distance(position, placedData->getPosition());

	// ���� ����� ���� ���
	if (placedDistance < placedData->getRadius())
	{
		auto nextNode = pathNodeList.front()->getMember().nextNode;
		auto nextData = inGame_node::getData(nextNode);
		float nextDistance = gFunc::Vec3Distance(position, nextData->getPosition());

		// ���� ����� ���� ��
		if (nextData->getRadius() < nextDistance)
		{
			// path ����
			_path->advance();
			placedNode = pathNodeList.front()->getMember().placedNode;

			return;
		}
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

	// Ž�� : ��ã��
	aStar_path* path = nullptr;
	auto placedNode = _bindCharacter->getPlacedNode();
	SGT_GAME->getSet().field->getMember().grape->pathfind(&path, placedNode, playerNode);

	// �׷��� ��ã��
	if (path == nullptr)
		SAFE_DELETE(_path);

	// ã�� : ����
	_path->connect(path, true, true);
}