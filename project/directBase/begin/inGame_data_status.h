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
	
	int current				= 0;		// ���� źȯ ��
	int reload				= 0;		// ��ü źȯ ��
	int maximum				= 0;		// �ִ� źȯ ��

	float shotDelay			= 1.0f;		// ���� �ӵ�
	float reloadDelay		= 1.0f;		// ���� �ӵ�

	float rebound			= 1.0f;		// �ݵ�
};