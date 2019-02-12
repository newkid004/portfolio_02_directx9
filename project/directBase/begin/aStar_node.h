#pragma once
#include "kGlobalDefine.h"
#include "pathfind_node.h"

#include "aStar_runner.h"

class aStar_node : public pathfind_node
{
public :
	struct nodeSet
	{
		aStar_node* connector;
		float distance;
	};
	struct info
	{
		D3DXVECTOR3 pos;
	};

public :
	typedef std::list<nodeSet> LIST;

private :
	int _index;

	LIST _linkedNodeList;

	info _info;

public :
	aStar_node* getClosestNode(aStar_node* dest);

public :
	int & getIndex(void) { return _index; }
	LIST & getLinkedNodeList(void) { return _linkedNodeList; }
	virtual void getInfo(info* & out) { out = &_info; }

public:
	aStar_node(D3DXVECTOR3 & position);
	~aStar_node();
};

