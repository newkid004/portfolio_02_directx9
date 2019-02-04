#pragma once
#include "kGlobalDefine.h"
#include "quadTree.h"

class quadTree_Frustum : public quadTree
{
public :
	enum CULL_PART
	{
		TL = 0b0001,
		LT = TL,

		TR = 0b0010,
		RT = TR,

		BL = 0b0100,
		LB = BL,

		BR = 0b1000,
		RB = BR,

		ALL = 0b1111,
		NONE = 0
	};

public :
	class node_frustum : public quadTree::node
	{
	protected :
		D3DXVECTOR3 _position = D3DXVECTOR3(0, 0, 0);

	protected :
		int chkFrustum(void);
		int chkFrustum(const D3DXVECTOR3 & offset);

	public:
		void cullFrustum(void);

	protected :
		virtual node* createChild(int TL, int TR, int BL, int BR);

		void putPosition(void);

	public :
		virtual void getPosition(D3DXVECTOR3 * out, const D3DXVECTOR3 & offset) override;
		void getPositionP(D3DXVECTOR3 ** out) { *out = &_position; };

	public:
		node_frustum(quadTree* bind, int sizeX, int sizeY);
		node_frustum(quadTree* bind, int TL, int TR, int BL, int BR);
	};

public :
	virtual void build(void) override;

public :
	void cullFrustum(void);

public:
	quadTree_Frustum(int sizeX, int sizeY);
	~quadTree_Frustum();
};

