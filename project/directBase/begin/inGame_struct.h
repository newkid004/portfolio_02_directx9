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

	float accelSpeed		= 4.0f;					// �ʴ� ���ӵ�
	float maximumSpeed		= 0.5f;					// �ִ� �̵��ӷ�
	float currentSpeed		= 0.0f;					// ���� �̵��ӵ�

	float velVertical		= 0.0f;					// ���� �ӵ�
	D3DXVECTOR2 velHorizon	= D3DXVECTOR2(0, 0);	// ���� �ӵ�

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
	int value				= 0;		// ���ط�
	
	float interfere			= 0.0f;		// �̵� ���ط�
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
	
	int current				= 0;		// ���� źȯ ��
	int reload				= 0;		// ��ü źȯ ��
	int maximum				= 0;		// �ִ� źȯ ��

	int damage				= 0;

	float shotDelay			= 1.0f;		// ���� �ӵ�
	float reloadDelay		= 1.0f;		// ���� �ӵ�

	float rebound			= 1.0f;		// �ݵ�

	float nextFireTime		= 0.0f;		// ���� �߻� ���ɽð�
	float nextReloadTime	= 0.0f;		// ���� ������ ���ɽð�
};