#pragma once
#include "kGlobalDefine.h"

class pathfind_node;

class pathfind_grape
{
public :
	struct breakNone
	{
		bool operator()(pathfind_node* n1, pathfind_node* n2) { return false; }
	};

public:
	pathfind_grape();
	~pathfind_grape();
};

