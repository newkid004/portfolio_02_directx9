#pragma once
#include "kGlobalDefine.h"

#define defType constexpr static float

struct inGame_value
{
	struct global
	{
		defType gravity			= 3.0f;
		defType friction		= 2.25f;	// �ʴ� ������
	
		defType PI				= D3DX_PI;
		defType PIPI			= D3DX_PI * 2.0f;
		defType P2I				= D3DX_PI / 2.0f;
	};

	struct enemy
	{
		defType delayHangOut	= 4.0f;		// �����Ÿ�		( ��Ž�� ���� )
		defType delayAlert		= 0.5f;		// ��� ����	( Ž�� Ȱ��ȭ )
		defType delayMove		= 0.05f;	// �̵� ����	( ª�� Ž���ֱ� )
		
		//defType delayAttack		= 1.25f;	// ���� ����
	};
};