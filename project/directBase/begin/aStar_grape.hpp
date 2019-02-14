#include "aStar_grape.h"

template<typename compare, typename breaker>
inline void aStar_grape::runGrape(const std::function<void(aStar_node*from, aStar_node*to)>& callback, breaker* brk, compare * view)
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
					callback(viewNode, linkedNode);
					if (brk)
					{
						if (isBreak = breaker()(viewNode, linkedNode))
							break;
					}
				}
				else
					openList.push(linkedIndex);
			}
		}

		if (isBreak)
			break;
	}
}
