#include "pickRay.h"

#include "managerList.h"

#include "direct3dApplication.h"
#include "camera.h"

#include "sceneBase.h"

void pick::createPickRay(ray * out_info)
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
	D3DXVECTOR3 & rayDir = out_info->direction;
	D3DXVECTOR3 & rayOrigin = out_info->origin;

	rayDir.x = pickPos.x * mWorld(0, 0) + pickPos.y * mWorld(1, 0) + pickPos.z * mWorld(2, 0);
	rayDir.y = pickPos.x * mWorld(0, 1) + pickPos.y * mWorld(1, 1) + pickPos.z * mWorld(2, 1);
	rayDir.z = pickPos.x * mWorld(0, 2) + pickPos.y * mWorld(1, 2) + pickPos.z * mWorld(2, 2);
	D3DXVec3Normalize(&rayDir, &rayDir);
	rayOrigin.x = mWorld(3, 0);
	rayOrigin.y = mWorld(3, 1);
	rayOrigin.z = mWorld(3, 2);
}

bool pick::chkPick(LPD3DXMESH mesh, ray * in_ray, info * out_info)
{
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