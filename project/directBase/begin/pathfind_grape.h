#pragma once
#include "kGlobalDefine.h"

class pathfind_node;

class pathfind_grape
{
public :
	struct takeFalse
	{
		bool operator()(void* viewData, pathfind_node* n1, pathfind_node* n2) { return false; }
	};
	struct takeTrue
	{
		bool operator()(void* viewData, pathfind_node* n1, pathfind_node* n2) { return true; }
	};

public:
	pathfind_grape();
	~pathfind_grape();
};

