#pragma once
#include "inGame_grape.h"

#include "managerList.h"
#include "gFunc.h"

#include "inGame_node.h"

#include "characterBase.h"

template<typename T>
inline void inGame_grape::putData(T & data, int listInterval, D3DXVECTOR3 & position, float radius)
{
	float closestDistance = FLT_MAX;

	for (int i = 0; i < _vNodeList.size(); ++i)
	{
		auto & viewNode = _vNodeList[i];
		auto & contant = _vBindList[i];
		float distance = gFunc::Vec2Distance(
			D3DXVECTOR2(contant->getPosition().x, contant->getPosition().z),
			D3DXVECTOR2(position.x, position.z));
		if (distance < contant->getRadius() + radius)
		{
			std::list<T>* viewList = ((std::list<T>*)&contant->getListSet()) + listInterval;
			viewList->push_back(data);

			if (1 < listInterval && distance < closestDistance)
			{
				((characterBase*)data)->getPlacedNode() = viewNode;
				closestDistance = distance;
			}
		}
	}
}