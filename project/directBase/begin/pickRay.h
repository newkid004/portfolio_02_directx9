#pragma once
#include "kGlobalDefine.h"

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

public :
	static void createPickRay(ray* out_info);
	static bool chkPick(LPD3DXMESH mesh, ray* in_ray, info* out_info);

private :
	pick() {};
	~pick() {};
};

