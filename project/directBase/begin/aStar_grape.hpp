#include "aStar_grape.h"

template<typename compare, typename breaker, typename continuer, typename pusher>
inline void aStar_grape::runGrape(void* viewData, const std::function<void(void* viewData, aStar_node*from, aStar_node*to)>& callback, breaker * brk, continuer * con, pusher* push, compare * view)
{
	auto & vNodeList = _vNodeList;

	if (vNodeList.empty())
		return;

	heap<int, compare> openList;
	heap<int, std::greater<>> closeList;

	bool isBreak = false;
	for (int i = 0; i < vNodeList.size(); ++i)
	{
		if (gMng::find(i, closeList.getContainer()))
			continue;

		openList.push(i);
		while (!openList.empty() && !isBreak)
		{
			int currentIndex = openList.top();
			auto viewNode = vNodeList[currentIndex];

			openList.pop();
			closeList.push(currentIndex);

			for (auto & i : viewNode->getLinkedNodeList())
			{
				auto linkedNode = i.connector;
				int linkedIndex = linkedNode->getIndex();

				if (gMng::find(linkedIndex, closeList.getContainer()))
					continue;

				if (!gMng::find(linkedIndex, openList.getContainer()))
				{
					callback(viewData, viewNode, linkedNode);
					if (brk)
					{
						if (isBreak = breaker()(viewData, viewNode, linkedNode))
							break;
					}
					if (con)
					{
						if (continuer()(viewData, viewNode, linkedNode))
							continue;
					}
				}
				else if(pusher()(viewData, viewNode, linkedNode))
					openList.push(linkedIndex);
			}
		}

		if (isBreak)
			break;
	}
}

template<typename compare, typename breaker, typename continuer, typename pusher>
inline void aStar_grape::runGrape(void* viewData, aStar_node * begin, const std::function<void(void* viewData, aStar_node*from, aStar_node*to)>& callback, breaker * brk, continuer * con, pusher* push, compare * view)
{
	auto & vNodeList = _vNodeList;

	if (vNodeList.empty())
		return;

	heap<int, compare> openList;
	heap<int, std::greater<>> closeList;

	bool isBreak = false;

	openList.push(begin->getIndex());
	while (!openList.empty() && !isBreak)
	{
		int currentIndex = openList.top();
		auto viewNode = vNodeList[currentIndex];

		openList.pop();
		closeList.push(currentIndex);

		for (auto & i : viewNode->getLinkedNodeList())
		{
			auto linkedNode = i.connector;
			int linkedIndex = linkedNode->getIndex();

			if (gMng::find(linkedIndex, closeList.getContainer()))
				continue;

			if (!gMng::find(linkedIndex, openList.getContainer()))
			{
				callback(viewData, viewNode, linkedNode);
				if (brk)
				{
					if (isBreak = breaker()(viewData, viewNode, linkedNode))
						break;
				}
				if (con)
				{
					if (continuer()(viewData, viewNode, linkedNode))
						continue;
				}
			}
			else if (pusher()(viewData, viewNode, linkedNode))
				openList.push(linkedIndex);
		}
	}
}