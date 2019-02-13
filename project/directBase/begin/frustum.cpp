#include "frustum.h"

#include "managerList.h"

#include "camera.h"
#include "sceneBase.h"

static D3DXVECTOR3 planeVertex[8] = {
	// near
	D3DXVECTOR3(-1.f,  1.f, 0.f),
	D3DXVECTOR3( 1.f,  1.f, 0.f),
	D3DXVECTOR3( 1.f, -1.f, 0.f),
	D3DXVECTOR3(-1.f, -1.f, 0.f),

	// far
	D3DXVECTOR3(-1.f,  1.f, 1.f),
	D3DXVECTOR3( 1.f,  1.f, 1.f),
	D3DXVECTOR3( 1.f, -1.f, 1.f),
	D3DXVECTOR3(-1.f, -1.f, 1.f)
};

frustum::frustum()
{
	ZeroMemory(_plane, sizeof(_plane));
}


frustum::~frustum()
{
}

void frustum::update(void)
{
	updatePlane();
}

void frustum::updatePlane(void)
{
	auto c = GET_CAMERA();

	D3DXMATRIXA16 mInverse = c->getMatrixView() * c->getMatrixProjection();
	D3DXMatrixInverse(&mInverse, NULL, &mInverse);
	
	D3DXVECTOR3 dublicateVertex[8];
	CopyMemory(dublicateVertex, planeVertex, sizeof(planeVertex));

	// view, projection 역행렬 적용
	for (D3DXVECTOR3 & vertex : dublicateVertex)
		D3DXVec3TransformCoord(&vertex, &vertex, &mInverse);


	// 절두체 평면 제작
	D3DXPlaneFromPoints(&_plane[0], &dublicateVertex[0], &dublicateVertex[3], &dublicateVertex[2]); //Near
	D3DXPlaneFromPoints(&_plane[1], &dublicateVertex[4], &dublicateVertex[5], &dublicateVertex[6]); //Far
	D3DXPlaneFromPoints(&_plane[2], &dublicateVertex[0], &dublicateVertex[4], &dublicateVertex[7]); //Left
	D3DXPlaneFromPoints(&_plane[3], &dublicateVertex[1], &dublicateVertex[2], &dublicateVertex[6]); //Right
	D3DXPlaneFromPoints(&_plane[4], &dublicateVertex[0], &dublicateVertex[1], &dublicateVertex[5]); //Top
	D3DXPlaneFromPoints(&_plane[5], &dublicateVertex[3], &dublicateVertex[7], &dublicateVertex[6]); //Bottom
}

bool frustum::isCull(const D3DXVECTOR3 & pos, int c)
{
	return chkCull(pos, 0, c);
}

bool frustum::isCull(const boundingSphere & bound, int c)
{
	return chkCull(bound.center, bound.radius, c);
}

bool frustum::chkCull(const D3DXVECTOR3 & dotPos, float interval, int c)
{
	if (c & CULL::NEAR_FAR)
	{
		for (int i = 0; i < 2; ++i)
		{
			if (D3DXPlaneDotCoord(&_plane[i], &dotPos) + interval < 0.0f)
				return true;
		}
	}

	if (c & CULL::LEFT_RIGHT)
	{
		for (int i = 2; i < 4; ++i)
		{
			if (D3DXPlaneDotCoord(&_plane[i], &dotPos) + interval < 0.0f)
				return true;
		}
	}

	if (c & CULL::TOP_BOT)
	{
		for (int i = 4; i < 6; ++i)
		{
			if (D3DXPlaneDotCoord(&_plane[i], &dotPos) + interval < 0.0f)
				return true;
		}
	}

	return false;
}

void frustum::getPlane(D3DXPLANE * outPlane[])
{
	*outPlane = _plane;
}
