#pragma once
#include "kGlobalDefine.h"

class pathfind_grape;

class pathfind_node
{
protected :
	pathfind_grape* _bindGrape = nullptr;

public :
	pathfind_grape* getBindGrape(void) { return _bindGrape; }

public:
	pathfind_node();
	~pathfind_node();
};

