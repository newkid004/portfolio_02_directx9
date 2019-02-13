#pragma once
#include "kGlobalDefine.h"

struct status_set
{
	int maxHp				= 0;
	int nowHp				= 0;

	D3DXVECTOR3 direction	= D3DXVECTOR3(0, 0, 0);
	float velocity			= 0;
};

struct attack_set
{
	int value				= 0;
};

struct weapon_set
{
	bool autoFire			= false;
	
	int current				= 0;		// 현재 탄환 수
	int reload				= 0;		// 교체 탄환 수
	int maximum				= 0;		// 최대 탄환 수

	float shotDelay			= 1.0f;		// 연사 속도
	float reloadDelay		= 1.0f;		// 장전 속도

	float rebound			= 1.0f;		// 반동
};