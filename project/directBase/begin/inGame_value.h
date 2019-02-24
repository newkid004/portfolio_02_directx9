#pragma once
#include "kGlobalDefine.h"

struct inGame_value
{
	struct global
	{
		globalReal gravity					= 3.0f;
		globalReal friction					= 2.25f;	// �ʴ� ������
	
		globalReal PI						= D3DX_PI;
		globalReal PIPI						= D3DX_PI * 2.0f;
		globalReal P2I						= D3DX_PI / 2.0f;
	};

	struct enemy
	{
		globalReal delayHangOut				= 4.0f;		// �����Ÿ�		( ��Ž�� ���� )
		globalReal delayAlert				= 0.5f;		// ��� ����	( Ž�� Ȱ��ȭ )
		globalReal delayMove				= 0.05f;	// �̵� ����	( ª�� Ž���ֱ� )

		globalReal aletyDistance			= 80.0f;
		globalReal findSomthingDistance		= 70.0f;
		
		//globalReal delayAttack		= 1.25f;	// ���� ����
	};

	struct bullet
	{
		globalReal speed					= 8.0f;
	};
};