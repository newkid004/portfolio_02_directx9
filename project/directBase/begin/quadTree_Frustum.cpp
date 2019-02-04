#include "quadTree_Frustum.h"

#include "managerList.h"
#include "sceneBase.h"
#include "frustum.h"

quadTree_Frustum::node_frustum::node_frustum(quadTree * bind, int sizeX, int sizeY) :
	node(bind, sizeX, sizeY)
{
	putPosition();
}

quadTree_Frustum::node_frustum::node_frustum(quadTree * bind, int TL, int TR, int BL, int BR) :
	node(bind, TL, TR, BL, BR)
{
	putPosition();
}

int quadTree_Frustum::node_frustum::chkFrustum(void)
{
	D3DXVECTOR3 treeOffset = _bindTree->getOffset();
	return (chkFrustum(treeOffset));
}

int quadTree_Frustum::node_frustum::chkFrustum(const D3DXVECTOR3 & offset)
{
	auto fru = GET_FRUSTUM();
	int cullType =
		frustum::CULL::NEAR_FAR |
		frustum::CULL::LEFT_RIGHT;

	int chkPart = 0;
	bool isInSphere = fru->chkCull(
		offset + _position,
		_radius,
		cullType);

	// 기본 경계구 확인
	if (!isInSphere)
		return CULL_PART::NONE;

	// 자식 경계구 확인
	for (int i = 0; i < 4; ++i)
	{
		node_frustum* child = (node_frustum*)_child[i];

		D3DXVECTOR3 * childPos;
		child->getPositionP(&childPos);

		bool isCull = fru->chkCull(offset + *childPos, child->getRadius(), cullType);
		chkPart |= isCull ? (1 << i) : 0;
	}

	return chkPart;
}

void quadTree_Frustum::node_frustum::cullFrustum(void)
{
	int cullPart = chkFrustum();

	switch (cullPart)
	{
	case CULL_PART::ALL:	// 완전 포함
		_isCull = false;
		return;

	case CULL_PART::NONE:	// 완전 제외
		_isCull = true;
		return;
	}

	// 일부 포함
	for (int i = 0; i < 4; ++i)
	{
		int viewBit = 1 << i;

		node_frustum* child = (node_frustum*)_child[i];
		if (cullPart & viewBit)
		{
			child->cullFrustum();
		}
		else
			child->_isCull = true;
	}
}

quadTree::node * quadTree_Frustum::node_frustum::createChild(int TL, int TR, int BL, int BR)
{
	return new node_frustum(_bindTree, TL, TR, BL, BR);
}

void quadTree_Frustum::node_frustum::putPosition(void)
{
	_position = D3DXVECTOR3(
		_center % _bindTree->getSize().x,
		0,
		_center / _bindTree->getSize().x
	);
}

void quadTree_Frustum::node_frustum::getPosition(D3DXVECTOR3 * out, const D3DXVECTOR3 & offset)
{
	*out = _position + offset;
}

// ----- tree ----- //
quadTree_Frustum::quadTree_Frustum(int sizeX, int sizeY) :
	quadTree(sizeX, sizeY)
{
}

quadTree_Frustum::~quadTree_Frustum()
{
}

void quadTree_Frustum::build(void)
{
	_root = new node_frustum(this, _size.x, _size.y);
	_root->build(_root);
}

void quadTree_Frustum::cullFrustum(void)
{
	return ((node_frustum*)_root)->cullFrustum();
}
