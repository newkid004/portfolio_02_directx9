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
	static bool chkPick(info* out_info, ray* in_ray, LPD3DXMESH mesh);

private :
	pick() {};
	~pick() {};
};

