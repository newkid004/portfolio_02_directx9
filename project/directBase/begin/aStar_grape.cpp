#include "aStar_grape.h"
#include "aStar_node.h"
#include "aStar_runner.h"
#include "aStar_path.h"

#include "gMng.h"
#include "gFunc.h"

#include "heap.h"

using namespace std;

aStar_grape::~aStar_grape()
{
	for (auto iter : _vNodeList)
		SAFE_DELETE(iter);
}

void aStar_grape::addNode(aStar_node * input)
{
	input->getBindGrape() = this;
	gMng::add(input, _vNodeList);

	input->getIndex() = _vNodeList.size() - 1;
}

bool aStar_grape::deleteNode(aStar_node * input)
{
	if (gMng::find(input, _vNodeList))
		return deleteNode(input->getIndex());

	return false;
}

bool aStar_grape::deleteNode(int index)
{
	SAFE_DELETE(_vNodeList[index]);
	_vNodeList.erase(_vNodeList.begin() + index);

	for (int i = index; i < _vNodeList.size(); ++i)
		_vNodeList[i]->getIndex() = i;

	return true;
}

bool aStar_grape::connectNode(aStar_node * n1, aStar_node * n2, bool reConnect)
{
	bool isConnected = false;
	auto & nodeConnection = n1->getLinkedNodeList();

	// 중복 시, 거리 재계산
	for (auto & iter : nodeConnection)
	{
		if (iter.connector == n2)
		{
			iter.distance = aStar_grape::calDistance(n1, n2);
			return true;
		}
	}

	float distance = aStar_grape::calDistance(n1, n2);
	nodeConnection.push_back(aStar_node::LIST::value_type({ n2, distance }));
	gMng::add(n2->getIndex(), _mConnection[n1->getIndex()]);

	if (reConnect)
		return connectNode(n2, n1, false);

	return true;
}

bool aStar_grape::connectNode(int index1, int index2)
{
	if (index1 < _vNodeList.size() && index2 < _vNodeList.size())
	{
		connectNode(_vNodeList[index1], _vNodeList[index2]);

		return true;
	}
	return false;
}

void aStar_grape::pathfind(aStar_path** out_path, aStar_node* sour, aStar_node* dest)
{
	vector<aStar_runner*> runnerContainer;
	heap<aStar_runner*, aStar_runner::comparer> openList;
	vector<aStar_runner*> closeList;

	_currentNode = sour;
	_destNode = dest;

	// calc start
	aStar_runner* runStart = new aStar_runner(_currentNode);
	openList.push(runStart);
	runnerContainer.push_back(runStart);

	while (!openList.empty())
	{
		// current runner
		aStar_runner* runner = openList.top();
		_currentNode = runner->getMember().placedNode;
		if (_currentNode == _destNode)
			break;

		openList.pop();
		closeList.push_back(runner);

		// closing node
		for (auto & iter : _currentNode->getLinkedNodeList())
		{
			aStar_node* viewNode = iter.connector;

			// close check
			bool isInCloseList = false;
			for (auto i : closeList)
			{
				if (viewNode == i->getMember().placedNode)
				{
					isInCloseList = true;
					break;
				}
			}
			if (isInCloseList)
				continue;

			// open check
			bool isInOpenList = false;
			for (auto i : openList)
			{
				if (viewNode == i->getMember().placedNode)
				{
					isInOpenList = true;

					// distance check
					if (runner->getMember().distance.G < i->getMember().distance.G)
						i->setPrevRunner(runner);

					break;
				}
			}

			// is not in openList
			if (!isInOpenList)
			{
				aStar_runner* traveler = new aStar_runner(runner, iter.connector);
				openList.push(traveler);
				runnerContainer.push_back(traveler);
			}
		}
	}

	// result
	*out_path = nullptr;
	if (!openList.empty())
	{
		std::list<aStar_runner*> resultPath;
		aStar_runner* backRunner = openList.top();

		while (backRunner->getMember().placedNode != sour)
		{
			resultPath.push_front(new aStar_runner(backRunner->getMember()));
			backRunner = backRunner->getMember().prevRunner;
		}
		resultPath.push_front(new aStar_runner(runStart->getMember()));

		*out_path = new aStar_path(resultPath);
	}

	// memory delete
	for (auto i : runnerContainer)
		SAFE_DELETE(i);
}

float aStar_grape::calDistance(aStar_node * n1, aStar_node * n2)
{
	aStar_node::info *infoA, *infoB;

	n1->getInfo(infoA);
	n2->getInfo(infoB);

	return gFunc::Vec3Distance(infoA->pos, infoB->pos);
}

float aStar_grape::calDistance(aStar_node * n, D3DXVECTOR3 & pos)
{
	aStar_node::info *info;

	n->getInfo(info);

	return gFunc::Vec3Distance(info->pos, pos);
}