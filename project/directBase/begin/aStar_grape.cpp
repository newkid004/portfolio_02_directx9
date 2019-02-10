#include "aStar_grape.h"
#include "aStar_node.h"
#include "aStar_runner.h"

#include "gMng.h"
#include "gFunc.h"

using namespace std;

aStar_grape::~aStar_grape()
{
	for (auto iter : _vNodeList)
		SAFE_DELETE(iter);
}

void aStar_grape::addNode(aStar_node * input)
{
	gMng::add(input, _vNodeList);
}

void aStar_grape::pathfind(std::stack<aStar_runner> & out_path, aStar_node* sour, aStar_node* dest)
{
	priority_queue<aStar_runner, vector<aStar_runner>, aStar_runner::comparer> openList;
	list<aStar_node*> closeList;

	_currentNode = sour;
	_destNode = dest;

	aStar_runner runStart(_currentNode);
	openList.push(runStart);

	while (!openList.empty())
	{
		aStar_runner* runner = (aStar_runner*)&openList.top();
		_currentNode = runner->getMember().placedNode;
		if (_currentNode == _destNode)
			break;

		openList.pop();
		closeList.push_back(_currentNode);

		for (auto & iter : _currentNode->getLinkedNodeList())
		{
			aStar_runner traveler(*runner, _currentNode);
			openList.push(runStart);
		}
	}

	if (!openList.empty())
	{
		aStar_runner* backRunner = (aStar_runner*)&openList.top();

		while (backRunner->getMember().placedNode != sour)
		{
			out_path.push(*backRunner);
			backRunner = backRunner->getMember().prevRunner;
		}
		out_path.push(runStart);
	}
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