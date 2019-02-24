#include "aStar_node.h"
#include "aStar_grape.h"
#include "aStar_runner.h"

#include "gFunc.h"

aStar_node::aStar_node(D3DXVECTOR3 & position)
{
	_info.pos = position;
}


aStar_node::~aStar_node()
{
	// 자신과 연결된 노드 중, 자신을 제거
	for (auto i : _linkedNodeList)
	{
		LIST & connectorNodeList = i.connector->getLinkedNodeList();
		for (auto iter = connectorNodeList.begin(); iter != connectorNodeList.end();)
		{
			if (this == iter->connector)
				iter = connectorNodeList.erase(iter);
			else
				++iter;
		}
	}
}

/*
float aStar_node::connect(aStar_node * connector, bool reConnect)
{
	// 중복 시, 거리 재계산
	for (auto & iter : _linkedNodeList)
	{
		if (iter.connector == connector)
			return iter.distance = aStar_grape::calDistance(this, connector);
	}

	float distance = aStar_grape::calDistance(this, connector);
	_linkedNodeList.push_back(LIST::value_type({connector, distance}));

	// 상호 연결
	if (reConnect)
		connector->connect(this, false);

	return distance;
}
*/

aStar_node * aStar_node::getClosestNode(aStar_node * dest)
{
	aStar_node* result = nullptr;
	float minDistance = FLT_MAX;

	for (auto & iter : _linkedNodeList)
	{
		float hDistance = aStar_grape::calDistance(iter.connector, dest);
		float fDistance = iter.distance + hDistance;

		if (fDistance < minDistance)
		{
			minDistance = fDistance;
			result = iter.connector;
		}
	}

	return result;
}

float aStar_node::getInterval(aStar_node * n1, aStar_node * n2)
{
	aStar_node::info *info1, *info2;
	n1->getInfo(info1);
	n2->getInfo(info2);

	return gFunc::Vec3Distance(info1->pos, info2->pos);
}
