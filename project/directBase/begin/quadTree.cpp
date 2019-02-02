#include "quadTree.h"


quadTree::quadTree(int sizeX, int sizeY)
{
	this->setEdge(
		0,
		sizeX - 1,
		sizeX * (sizeY - 1),
		sizeX * sizeY - 1);
}

quadTree::quadTree(quadTree * parent)
{
}

quadTree::~quadTree()
{
	for (int i = 0; i < 4; ++i)
		SAFE_DELETE(_child[i]);
}

quadTree * quadTree::createChild(int TL, int TR, int BL, int BR)
{
	quadTree* child;

	child = new quadTree(this);
	child->setEdge(TL, TR, BL, BR);

	return child;
}

bool quadTree::setEdge(int TL, int TR, int BL, int BR)
{
	EDGE(edge::TL) = TL;
	EDGE(edge::TR) = TR;
	EDGE(edge::BL) = BL;
	EDGE(edge::BR) = BR;
	_center = (TL + TR + BL + BR) / 4;

	return true;
}

bool quadTree::subDivide(void)
{
	// 분할가능 여부 판단
	if (EDGE(edge::TR) - EDGE(edge::TL) <= 1)
		return false;

	// 각 변 중점위치
	int centerTop = (EDGE(edge::TL) + EDGE(edge::TR)) / 2;
	int centerBot = (EDGE(edge::BL) + EDGE(edge::BR)) / 2;
	int centerLft = (EDGE(edge::TL) + EDGE(edge::BL)) / 2;
	int centerRgt = (EDGE(edge::TR) + EDGE(edge::BR)) / 2;

	// 자식 추가(분할)
	CHILD(edge::TL) = createChild(EDGE(edge::TL), centerTop, centerLft, _center);
	CHILD(edge::TR) = createChild(centerTop, EDGE(edge::TR), _center, centerRgt);
	CHILD(edge::BL) = createChild(centerLft, _center, EDGE(edge::BL), centerBot);
	CHILD(edge::BR) = createChild(_center, centerRgt, centerBot, EDGE(edge::BR));

	return true;
}

int & quadTree::EDGE(edge e)
{
	return _edge[(int)e];
}

quadTree *& quadTree::CHILD(edge e)
{
	return _child[(int)e];
}
