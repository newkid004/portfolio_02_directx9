#pragma once
#include "kGlobalDefine.h"

class renderObject;

class pick
{
public :
	struct ray
	{
		D3DXVECTOR3 direction;
		D3DXVECTOR3 origin;
	};

	struct info
	{
		LPD3DXMESH mesh;
		BOOL isHit;
		DWORD faceIndex;
		D3DXVECTOR2 uv;
		FLOAT distance;
	};

public:
	static void createPickRay(ray* out_ray, D3DXMATRIXA16 * mObjWorld = nullptr);
	static void applyMatrix(ray* out_ray, ray* in_ray, D3DXMATRIXA16 * mObjWorld);

	// 만일 in_ray == NULL 이라면, 마우스 <-> 화면 pickRay 적용
	static bool chkPick(info* out_info, ray* in_ray, LPD3DXMESH mesh);
	static bool chkPick(D3DXVECTOR3* out_info, ray* in_ray, const D3DXPLANE* plane);
	static bool chkPick(ray* in_ray, renderObject* sMesh, EDebugDrawType type = EDebugDrawType::SPHERE);
	static bool isPickRay2Box(ray* in_ray, D3DXVECTOR3 * outCollisionPos, float speed, boundingBox * bBox);
	static bool isPickRay2Sphere(ray* in_ray, D3DXVECTOR3 * outCollisionPos, float speed, boundingSphere * bSphere);
	

	static bool chkPick(ray* in_ray, boundingBox* bBox);
	static bool chkPick(ray* in_ray, boundingSphere* bSphere);

private :
	pick() {};
	~pick() {};
};

