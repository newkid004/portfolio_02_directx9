#include "pickRay.h"

#include "managerList.h"
#include "gFunc.h"

#include "sceneBase.h"
#include "direct3dApplication.h"
#include "camera.h"
#include "renderObject.h"

void pick::createPickRay(ray * out_ray, D3DXMATRIXA16 * mObjWorld)
{
	// 클릭 좌표 확인
	D3DVIEWPORT9 viewPort;
	MN_DEV->GetViewport(&viewPort);

	D3DXVECTOR3 pickPos;
	D3DXMATRIXA16 & mProjection = GET_CAMERA()->getMatrixProjection();
	pickPos.x = (((2.0f * MN_KEY->getMousePos().x) / viewPort.Width) - 1.0f - mProjection._31) / mProjection._11;
	pickPos.y = -(((2.0f * MN_KEY->getMousePos().y) / viewPort.Height) - 1.0f - mProjection._32) / mProjection._22;
	pickPos.z = 1.0f;

	// 뷰, 월드 역행렬
	D3DXMATRIXA16 mWorld = GET_CAMERA()->getMatrixFinal() * GET_CAMERA()->getMatrixView();
	D3DXMatrixInverse(&mWorld, NULL, &GET_CAMERA()->getMatrixView());

	// 클릭 좌표 2D -> 3D 변환
	D3DXVECTOR3 & rayDir = out_ray->direction;
	D3DXVECTOR3 & rayOrigin = out_ray->origin;

	rayDir.x = pickPos.x * mWorld(0, 0) + pickPos.y * mWorld(1, 0) + pickPos.z * mWorld(2, 0);
	rayDir.y = pickPos.x * mWorld(0, 1) + pickPos.y * mWorld(1, 1) + pickPos.z * mWorld(2, 1);
	rayDir.z = pickPos.x * mWorld(0, 2) + pickPos.y * mWorld(1, 2) + pickPos.z * mWorld(2, 2);
	D3DXVec3Normalize(&rayDir, &rayDir);
	rayOrigin.x = mWorld(3, 0);
	rayOrigin.y = mWorld(3, 1);
	rayOrigin.z = mWorld(3, 2);

	if (mObjWorld != nullptr)
		applyMatrix(out_ray, out_ray, mObjWorld);
}

void pick::applyMatrix(ray * out_ray, ray * in_ray, D3DXMATRIXA16 * mObjWorld)
{
	if (in_ray == NULL)
		in_ray = &MN_KEY->getPickRay();

	D3DXMATRIXA16 mObjInv;
	D3DXMatrixInverse(&mObjInv, NULL, mObjWorld);

	D3DXVec3TransformNormal(&out_ray->direction, &in_ray->direction, &mObjInv);
	D3DXVec3TransformCoord(&out_ray->origin, &in_ray->origin, &mObjInv);
}

bool pick::chkPick(info* out_info, ray* in_ray, LPD3DXMESH mesh)
{
	if (in_ray == NULL)
		in_ray = &MN_KEY->getPickRay();

	D3DXVECTOR3 & rayDir = in_ray->direction;
	D3DXVECTOR3 & rayOrigin = in_ray->origin;

	// 충돌 검사
	out_info->mesh = mesh;

	D3DXIntersect(
		out_info->mesh,
		&rayOrigin,
		&rayDir,
		&out_info->isHit,
		&out_info->faceIndex,
		&out_info->uv.x,
		&out_info->uv.y,
		&out_info->distance,
		NULL,
		NULL);

	return out_info->isHit == TRUE;
}

bool pick::chkPick(D3DXVECTOR3 * out_info, ray * in_ray, const D3DXPLANE * plane)
{
	if (in_ray == NULL)
		in_ray = &MN_KEY->getPickRay();

	D3DXVECTOR3 planeVector(plane->a, plane->b, plane->c);

	float dotOrigin = D3DXVec3Dot(&planeVector, &in_ray->origin);
	float dotDir = D3DXVec3Dot(&planeVector, &in_ray->direction);

	if (dotDir == 0)
		return false;

	float distance = -(dotOrigin + plane->d) / dotDir;

	*out_info = in_ray->origin + (in_ray->direction * distance);

	if (distance < 0)
		return false;

	return true;
}

bool pick::chkPick(ray * in_ray, renderObject * sMesh, EDebugDrawType type)
{
	if (in_ray == NULL)
		in_ray = &MN_KEY->getPickRay();

	switch (type)
	{
	case EDebugDrawType::BOX: {
		objectBox objBox;
		boundingBox bndBox;
		sMesh->getObjectBox(&objBox);
		gFunc::obj2bound(&bndBox, &objBox);

		return chkPick(in_ray, &bndBox);

	} break;

	case EDebugDrawType::SPHERE: {
		boundingSphere bndSphere;
		sMesh->getBoundingSphereFinal(&bndSphere);

		return chkPick(in_ray, &bndSphere);
	} break;

	}

	return false;
}

bool pick::chkPick(ray * in_ray, boundingBox * bBox)
{
	if (in_ray == NULL)
		in_ray = &MN_KEY->getPickRay();

	D3DXVECTOR3 & rayDir = in_ray->direction;
	D3DXVECTOR3 & rayOrigin = in_ray->origin;

	float value_mM = -FLT_MAX;
	float value_Mm = FLT_MAX;

	for (int i = 0; i < 3; ++i)
	{
		float viewRayDir = *(((float*)&rayDir) + i);
		float viewRayOrigin = *(((float*)&rayOrigin) + i);

		float viewBoxMin = *(((float*)&bBox->min) + i);
		float viewBoxMax = *(((float*)&bBox->max) + i);

		if (fabsf(viewRayDir) <= FLT_EPSILON)
		{
			if (viewRayOrigin < viewBoxMin || viewBoxMax < viewRayOrigin)
				return false;
		}
		else
		{
			float minValue = (viewBoxMin - viewRayOrigin) / viewRayDir;
			float maxValue = (viewBoxMax - viewRayOrigin) / viewRayDir;

			if (maxValue < minValue)
				std::swap(maxValue, minValue);

			if (value_mM < minValue) value_mM = minValue;
			if (maxValue < value_Mm) value_Mm = maxValue;

			if (value_Mm < 0.0f || value_Mm < value_mM)
				return false;
		}
	}

	return true;
}

bool pick::chkPick(ray * in_ray, boundingSphere * bSphere)
{
	if (in_ray == NULL)
		in_ray = &MN_KEY->getPickRay();

	D3DXVECTOR3 & rayDir = in_ray->direction;
	D3DXVECTOR3 & rayOrigin = in_ray->origin;

	D3DXVECTOR3 delta = bSphere->center - rayOrigin;
	float deltaLength = D3DXVec3Dot(&delta, &delta);
	float radius = bSphere->radius * bSphere->radius;
	float dotValue = D3DXVec3Dot(&delta, &rayDir);

	if (dotValue < 0.0f && deltaLength > radius)
		return false;

	return deltaLength - (dotValue * dotValue) <= radius;
}
