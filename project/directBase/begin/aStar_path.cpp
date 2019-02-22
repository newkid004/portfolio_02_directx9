#include "aStar_path.h"

#include "aStar_node.h"
#include "aStar_grape.h"
#include "aStar_runner.h"

aStar_path::aStar_path(std::list<aStar_runner*> & p) :
	_path(p)
{
	auto iterFront = _path.begin();
	auto iterBack = iterFront;

	++iterFront;
	while (iterFront != _path.end())
	{
		(*iterFront)->setPrevRunner(*iterBack);

		++iterFront;
		++iterBack;
	}

	_distance = calDistance();
}

aStar_path::~aStar_path()
{
	for (auto i : _path)
		SAFE_DELETE(i);
}

bool aStar_path::connect(aStar_path * connection, bool isDelete, bool isConnectable)
{
	bool connectable = isConnectable ? true : (_path.back()->getMember().placedNode == connection->_path.front()->getMember().placedNode);

	if (connectable)
	{
		bool isDelete = eraseBack();
		if (isDelete && 0 < _path.size())
			connection->_path.front()->getMember().prevRunner = _path.back();

		for (auto & i : connection->_path)
		{
			auto addition = new aStar_runner(i->getMember());
			if(_path.size() != 0)	
				addition->setPrevRunner(_path.back());

			_path.push_back(addition);
		}

		if (isDelete)
			SAFE_DELETE(connection);

		calDistance();

		return true;
	}

	return false;
}

bool aStar_path::connectAuto(aStar_path * connection, bool isDelete)
{
	bool isConnectable = _path.back()->getMember().placedNode == connection->_path.front()->getMember().placedNode;

	if (isConnectable)
		return connect(connection, isDelete, true);

	else
	{
		auto sourNode = _path.back()->getMember().placedNode;
		auto destNode = _path.front()->getMember().placedNode;
		auto grape = (aStar_grape*)sourNode->getBindGrape();

		aStar_path* result = nullptr;
		grape->pathfind(&result, sourNode, destNode);

		if (result == nullptr)
			return false;

		connect(result, true, true);
		connect(connection, isDelete, true);

		return true;
	}

	return false;
}

bool aStar_path::eraseFront(void)
{
	if (!_path.empty())
	{
		float interval =
			_path.front()->getMember().nextRunner->getMember().distance.G -
			_path.front()->getMember().distance.G;

		delete _path.front();
		_path.erase(_path.begin());

		if (!_path.empty())
		{
			_path.front()->getMember().prevNode = nullptr;
			_path.front()->getMember().prevRunner = nullptr;
		}

		for (auto & i : _path)
			i->getMember().distance.G -= interval;

		calDistance();

		return true;
	}
	return false;
}

bool aStar_path::eraseBack(void)
{
	if (!_path.empty())
	{
		delete _path.back();
		_path.erase(--_path.end());

		if (!_path.empty())
		{
			_path.back()->getMember().nextNode = nullptr;
			_path.back()->getMember().nextRunner = nullptr;
		}

		calDistance();

		return true;
	}
	return false;
}      

void aStar_path::advance(void)
{
	if (eraseFront())
	{
		auto & member = _path.front()->getMember();
		member.prevNode = nullptr;
		member.prevRunner = nullptr;
	}
}

bool aStar_path::cutTail(aStar_node * dest)
{
	aStar_runner* curRunner = _path.back();

	if (dest == nullptr)
		return eraseBack();

	bool isFind = false;
	while (auto prev = curRunner->getMember().prevRunner)
	{
		if (prev->getMember().placedNode == dest)
		{
			isFind = true;
			break;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
		}

		curRunner = prev;
	}

	if (isFind)
	{
		while (_path.back()->getMember().placedNode != dest)
			eraseBack();
	}

	return isFind;
}

aStar_runner * aStar_path::putTail(aStar_node * dest)
{
	aStar_runner* result = new aStar_runner(_path.back(), dest);
	_path.push_back(result);
	
	calDistance();

	return result;
}

float aStar_path::calDistance(void)
{
	if (_path.size() == 0) return 0;
	return _distance = _path.back()->getMember().distance.G;
}
