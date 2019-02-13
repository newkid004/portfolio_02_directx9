#pragma once
#include "kGlobalDefine.h"

class pathfind_grape;

class pathfind_node
{
protected :
	pathfind_grape*	_bindGrape = nullptr;
	void*			_bindData = nullptr;

public :
	pathfind_grape*	& getBindGrape(void) { return _bindGrape; }
	void* & getBindData(void) { return _bindData; }

public:
	pathfind_node();
	~pathfind_node();
};

