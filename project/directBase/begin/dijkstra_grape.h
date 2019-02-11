#pragma once
#include "kGlobalDefine.h"
#include "pathfind_grape.h"

class dijkstra_node;

class dijkstra_grape : public pathfind_grape
{
public :
	std::vector<dijkstra_node*> _vNodeList;

public:
	dijkstra_grape();
	~dijkstra_grape();
};

