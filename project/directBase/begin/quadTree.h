#pragma once
#include "kGlobalDefine.h"

class quadTree
{
public :
	enum class edge 
	{
		TL = 0, TR = 1,
		BL = 2, BR = 3,

		LT = 0, RT = 1,
		LB = 2, RB = 3
	};

protected :
	quadTree* _child[4] = { NULL, };

	int _center = 0.0f;
	int _edge[4] = { 0, };
	float _radius = 0.0f;

protected :
	virtual quadTree* createChild(int TL, int TR, int BL, int BR);
	bool setEdge(int TL, int TR, int BL, int BR);
	bool subDivide(void);

	int & EDGE(edge e);
	quadTree* & CHILD(edge e);

public:
	quadTree(int sizeX, int sizeY);
	quadTree(quadTree* parent);
	~quadTree();
};

