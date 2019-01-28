#include "pickRay.h"

#include "managerList.h"
#include "gFunc.h"

#include "sceneBase.h"
#include "direct3dApplication.h"
#include "camera.h"
#include "renderObject.h"

void pick::createPickRay(ray * out_ray, D3DXMATRIXA16 * mObjWorld)
{
	// Ŭ�� ��ǥ Ȯ��
	D3DVIEWPORT9 viewPort;
	MN_DEV->GetViewport(&viewPort);

	D3DXVECTOR3 pickPos;
	D3DXMATRIXA16 & mProjection = GET_CAMERA()->getMatrixProjection();
	pickPos.x = (((2.0f * MN_KEY->getMousePos().x) / viewPort.Width) - 1.0f - mProjection._31) / mProjection._11;
	pickPos.y = -(((2.0f * MN_KEY->getMousePos().y) / viewPort.Height) - 1.0f - mProjection._32) / mProjection._22;
	pickPos.z = 1.0f;

	// ��, ���� �����
	D3DXMATRIXA16 mWorld = GET_CAMERA()->getMatrixFinal() * GET_CAMERA()->getMatrixView();
	D3DXMatrixInverse(&mWorld, NULL, &GET_CAMERA()->getMatrixView());

	// Ŭ�� ��ǥ 2D -> 3D ��ȯ
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
	{
		D3DXMATRIXA16 mObjInv;
		D3DXMatrixInverse(&mObjInv, NULL, mObjWorld);

		D3DXVec3TransformNormal(&rayDir, &rayDir, &mObjInv);
		D3DXVec3TransformCoord(&rayOrigin, &rayOrigin, &mObjInv);
	}
}

bool pick::chkPick(info* out_info, ray* in_ray, LPD3DXMESH mesh)
{
	D3DXVECTOR3 & rayDir = in_ray->direction;
	D3DXVECTOR3 & rayOrigin = in_ray->origin;

	// �浹 �˻�
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

bool pick::chkPick(ray * in_ray, renderObject * sMesh, EDebugDrawType type)
{
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
}

bool pick::chkPick(ray * in_ray, boundingBox * bBox)
{
	D3DXVECTOR3 & rayDir = in_ray->direction;
	D3DXVECTOR3 & rayOrigin = in_ray->origin;

	float value_mM = -FLT_MAX;
	float value_Mm = FLT_MAX;

	// x
	if (fabsf(rayDir.x) <= FLT_EPSILON)
	{
		if (rayOrigin.x < bBox->min.x || bBox->max.x < rayOrigin.x)
			return false;
	}
	else
	{
		float minValue = (bBox->min.x - rayOrigin.x) / rayDir.x;
		float maxValue = (bBox->max.x - rayOrigin.x) / rayDir.x;

		if (maxValue < minValue)
			std::swap(maxValue, minValue);

		if (value_mM < minValue) value_mM = minValue;
		if (maxValue < value_Mm) value_Mm = maxValue;

		if (value_Mm < 0.0f || value_Mm < value_mM)
			return false;
	}

	// y
	if (fabsf(rayDir.y) <= FLT_EPSILON)
	{
		if (rayOrigin.y < bBox->min.y || bBox->max.y < rayOrigin.y)
			return false;
	}
	else
	{
		float minValue = (bBox->min.y - rayOrigin.y) / rayDir.y;
		float maxValue = (bBox->max.y - rayOrigin.y) / rayDir.y;

		if (maxValue < minValue)
			std::swap(maxValue, minValue);

		if (value_mM < minValue) value_mM = minValue;
		if (maxValue < value_Mm) value_Mm = maxValue;

		if (value_Mm < 0.0f || value_Mm < value_mM)
			return false;
	}

	// z
	if (fabsf(rayDir.z) <= FLT_EPSILON)
	{
		if (rayOrigin.z < bBox->min.z || bBox->max.z < rayOrigin.z)
			return false;
	}
	else
	{
		float minValue = (bBox->min.z - rayOrigin.z) / rayDir.z;
		float maxValue = (bBox->max.z - rayOrigin.z) / rayDir.z;

		if (maxValue < minValue)
			std::swap(maxValue, minValue);

		if (value_mM < minValue) value_mM = minValue;
		if (maxValue < value_Mm) value_Mm = maxValue;

		if (value_Mm < 0.0f || value_Mm < value_mM)
			return false;
	}

	return true;
}

bool pick::chkPick(ray * in_ray, boundingSphere * bSphere)
{
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
