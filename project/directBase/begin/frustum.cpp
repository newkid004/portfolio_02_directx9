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

	// view, projection ����� ����
	for (D3DXVECTOR3 & vertex : planeVertex)
		D3DXVec3TransformCoord(&vertex, &vertex, &mInverse);

	// ����ü ��� ����
	D3DXPlaneFromPoints(&_plane[0], &planeVertex[0], &planeVertex[3], &planeVertex[2]); //Near
	D3DXPlaneFromPoints(&_plane[1], &planeVertex[4], &planeVertex[5], &planeVertex[6]); //Far
	D3DXPlaneFromPoints(&_plane[2], &planeVertex[0], &planeVertex[4], &planeVertex[7]); //Left
	D3DXPlaneFromPoints(&_plane[3], &planeVertex[1], &planeVertex[2], &planeVertex[6]); //Right
	D3DXPlaneFromPoints(&_plane[4], &planeVertex[0], &planeVertex[1], &planeVertex[5]); //Top
	D3DXPlaneFromPoints(&_plane[5], &planeVertex[3], &planeVertex[7], &planeVertex[6]); //Bottom
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
