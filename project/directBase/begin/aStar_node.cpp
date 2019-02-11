#include "aStar_node.h"
#include "aStar_grape.h"

aStar_node::aStar_node(D3DXVECTOR3 position)
{
	_info.pos = position;
}


aStar_node::~aStar_node()
{
}

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

void aStar_node::calcDistance(aStar_runner::info_distance * out_distance, aStar_node * toNode)
{
	aStar_node* dest = ((aStar_grape*)_bindGrape)->getDestNode();

	out_distance->G = aStar_grape::calDistance(this, toNode);
	out_distance->H = aStar_grape::calDistance(this, dest);
	out_distance->F = out_distance->G + out_distance->H;
}

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
