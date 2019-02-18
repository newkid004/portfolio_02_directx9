#pragma once
#include "kGlobalDefine.h"


struct character_set
{
	int status				= 0;

	float colRadius			= 1.0f;

	int maxHp				= 1;
	int nowHp				= 1;

};

struct move_set
{
	int status				= 0;

	float accelSpeed		= 4.0f;					// 초당 가속도
	float maximumSpeed		= 0.5f;					// 최대 이동속력
	float currentSpeed		= 0.0f;					// 현재 이동속도

	float velVertical		= 0.0f;					// 수직 속도
	D3DXVECTOR2 velHorizon	= D3DXVECTOR2(0, 0);	// 수평 속도

	float getSpeedTotal(void)			{ return D3DXVec3Length(&getVelocityXYZ()); }
	float getSpeedXZ(void)				{ return D3DXVec2Length(&velHorizon); }
	D3DXVECTOR3 getVelocityXYZ(void) 	{ return D3DXVECTOR3(velHorizon.x, velVertical, velHorizon.y); }
	D3DXVECTOR3 getVelocityXZ2CurruntSpeed(void)
	{ 
		D3DXVECTOR3 velXZ;
		velXZ.x = velHorizon.x;
		velXZ.z = velHorizon.y;
		D3DXVec3Normalize(&velXZ, &velXZ);

		velXZ.x = velXZ.x * currentSpeed;
		velXZ.y = velVertical;
		velXZ.z = velXZ.z * currentSpeed;

		return velXZ;
	}
};

struct attack_set
{
	int value				= 0;		// 피해량
	
	float interfere			= 0.0f;		// 이동 방해량
};

struct weapon_set
{
	struct type
	{
		static constexpr int none = 0;
		static constexpr int rifle = 1;
		static constexpr int shotgun = 2;
		static constexpr int healkit = 3;
	};

	int type = 0;

	int status				= 0;

	bool autoFire			= false;
	
	int current				= 0;		// 현재 탄환 수
	int reload				= 0;		// 교체 탄환 수
	int maximum				= 0;		// 최대 탄환 수

	int damage				= 0;

	float shotDelay			= 1.0f;		// 연사 속도
	float reloadDelay		= 1.0f;		// 장전 속도

	float rebound			= 1.0f;		// 반동

	float nextFireTime		= 0.0f;		// 다음 발사 가능시간
	float nextReloadTime	= 0.0f;		// 다음 재장전 가능시간
};