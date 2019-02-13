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

	class node
	{
	protected :
		quadTree* _bindTree;

		node* _child[4] = { NULL, };

		int _center = 0.0f;
		int _edge[4] = { 0, };

		bool _isCull = false;
		float _radius = 0.0f;

	protected :
		bool setEdge(int TL, int TR, int BL, int BR);
		virtual node* createChild(int TL, int TR, int BL, int BR);
		bool subDivide(void);

	public:
		bool build(node* parent);
		bool isVisible(void);

	public :
		virtual void getPosition(D3DXVECTOR3 * out);
		virtual void getPosition(D3DXVECTOR3 * out, const D3DXVECTOR3 & offset);
		float getRadius(void) { return _radius; }

		int & EDGE(edge e);
		node* & CHILD(edge e);

	public :
		node(quadTree* bind, int sizeX, int sizeY);
		node(quadTree* bind, int TL, int TR, int BL, int BR);
		~node(void);
	};

protected :
	node* _root = nullptr;

	POINT _size = POINT{ 0, 0 };
	D3DXVECTOR3 _position = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 _scale = D3DXVECTOR3(1, 1, 1);

public :
	virtual void build(void);

public :
	const POINT & getSize(void) { return _size; }
	const D3DXVECTOR3 & getPosition(void) { return _position; }
	const D3DXVECTOR3 & getScale(void) { return _scale; }
	
	D3DXVECTOR3 getOffset(void);

public:
	quadTree(int sizeX, int sizeY);
	virtual ~quadTree();
};

