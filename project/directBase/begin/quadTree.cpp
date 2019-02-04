#include "quadTree.h"

#include "gFunc.h"

quadTree::node::node(quadTree* bind, int sizeX, int sizeY) :
	_bindTree(bind)
{
	this->setEdge(
		0,
		sizeX - 1,
		sizeX * (sizeY - 1),
		sizeX * sizeY - 1);
}

quadTree::node::node(quadTree* bind, int TL, int TR, int BL, int BR) :
	_bindTree(bind)
{
	this->setEdge(
		TL, TR, 
		BL, BR);
}

quadTree::node::~node(void)
{
	for (int i = 0; i < 4; ++i)
		SAFE_DELETE(_child[i]);
}

bool quadTree::node::setEdge(int TL, int TR, int BL, int BR)
{
	EDGE(edge::TL) = TL;
	EDGE(edge::TR) = TR;
	EDGE(edge::BL) = BL;
	EDGE(edge::BR) = BR;
	_center = (TL + TR + BL + BR) / 4;

	return true;
}

quadTree::node * quadTree::node::createChild(int TL, int TR, int BL, int BR)
{
	return new node(_bindTree, TL, TR, BL, BR);
}

bool quadTree::node::subDivide(void)
{
	// 각 변 중점위치
	int centerTop = (EDGE(edge::TL) + EDGE(edge::TR)) / 2;
	int centerBot = (EDGE(edge::BL) + EDGE(edge::BR)) / 2;
	int centerLft = (EDGE(edge::TL) + EDGE(edge::BL)) / 2;
	int centerRgt = (EDGE(edge::TR) + EDGE(edge::BR)) / 2;

	// 분할가능 여부 판단
	if (isVisible())
		return false;

	// 자식 추가(분할)
	CHILD(edge::TL) = createChild(EDGE(edge::TL), centerTop, centerLft, _center);
	CHILD(edge::TR) = createChild(centerTop, EDGE(edge::TR), _center, centerRgt);
	CHILD(edge::BL) = createChild(centerLft, _center, EDGE(edge::BL), centerBot);
	CHILD(edge::BR) = createChild(_center, centerRgt, centerBot, EDGE(edge::BR));

	return true;
}

bool quadTree::node::build(node * parent)
{
	if (subDivide())
	{
		float radius2 = (parent->EDGE(edge::BR) - parent->EDGE(edge::TL)) / 2;

		_radius = radius2 / 2.0f;

		CHILD(edge::TL)->build(this);
		CHILD(edge::TR)->build(this);
		CHILD(edge::BL)->build(this);
		CHILD(edge::BR)->build(this);
	}
	return true;
}

bool quadTree::node::isVisible(void)
{
	return EDGE(edge::TR) - EDGE(edge::TL) <= 1;
}

void quadTree::node::getPosition(D3DXVECTOR3 * out)
{
	return getPosition(out, _bindTree->getOffset());
}

void quadTree::node::getPosition(D3DXVECTOR3 * out, const D3DXVECTOR3 & offset)
{
	*out = 
		offset +
		D3DXVECTOR3(
			_center % _bindTree->getSize().x, 0,
			_center / _bindTree->getSize().x);
}

int & quadTree::node::EDGE(edge e)
{
	return _edge[(int)e];
}

quadTree::node *& quadTree::node::CHILD(edge e)
{
	return _child[(int)e];
}


// quadTree
quadTree::quadTree(int sizeX, int sizeY)
{
	_size = POINT{ (LONG)sizeX, (LONG)sizeY };
}

quadTree::~quadTree()
{
	SAFE_DELETE(_root);
}

void quadTree::build(void)
{
	_root = new node(this, _size.x, _size.y);
	_root->build(_root);
}

D3DXVECTOR3 quadTree::getOffset(void)
{
	return D3DXVECTOR3(
		_position.x - (_size.x * _scale.x),
		_position.y,
		_position.z - (_size.y * _scale.z));
}