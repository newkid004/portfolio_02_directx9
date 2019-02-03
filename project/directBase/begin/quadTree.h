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
		node* _child[4] = { NULL, };

		int _center = 0.0f;
		int _edge[4] = { 0, };

		bool _isCull = false;
		float _radius = 0.0f;

	protected :
		bool setEdge(int TL, int TR, int BL, int BR);
		virtual node* createChild(int TL, int TR, int BL, int BR);
		bool subDivide(void);

	public :
		int & EDGE(edge e);
		node* & CHILD(edge e);

	public :
		node(quadTree* tree, int sizeX, int sizeY);
		node(quadTree* tree, int TL, int TR, int BL, int BR);
		~node(void);
	};


protected :
	node* _root = nullptr;
	std::vector<bool*> _vIsCull;



public:
	quadTree(int sizeX, int sizeY);
	~quadTree();
};

