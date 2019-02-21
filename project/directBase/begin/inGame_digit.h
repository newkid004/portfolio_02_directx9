#pragma once
#include "kGlobalDefine.h"

struct inGame_digit
{
	struct KEY
	{
		globalDigit W			= 1 << 0x0;
		globalDigit S			= 1 << 0x1;
		globalDigit A			= 1 << 0x2;
		globalDigit D			= 1 << 0x3;
	};

	// ���� : ĳ����
	struct MOVE
	{
		globalDigit MOVEING		= 1 << 0x0;
		globalDigit LAND		= 1 << 0x1;
		globalDigit FLOAT		= 1 << 0x2;

		globalDigit NONE		= 0;
	};

	// ���� : ĳ����, AI
	struct CHAR
	{
		globalDigit IDLE		= 1 << 0x0;		// �⺻ ����
		globalDigit ALERT		= 1 << 0x1;		// ��� ����
		globalDigit APPROACH	= 1 << 0x2;		// ���� ����
		globalDigit ADJACENT	= 1 << 0x3;		// ���� ����
		globalDigit ATTACK		= 1 << 0x4;		// ���� ����
		globalDigit LROTATE		= 1 << 0x5;		// lȸ�� ����
		globalDigit RROTATE		= 1 << 0x6;		// rȸ�� ����
		globalDigit FALL		= 1 << 0x7;		// �������� ����
		globalDigit BESHOT		= 1 << 0x8;		// �ǰ� ����
		globalDigit SHOVED		= 1 << 0x9;		// ������ ���� 

		globalDigit DEAD		= 1 << 0x1f;

		globalDigit NONE		= 0;
	};

	struct ENEMY
	{
		globalDigit COMMON		= 1 << 0x0;		// �Ϲ� ����
		globalDigit TANK		= 1 << 0x1;		// ��ũ

		globalDigit NONE		= 0;
	};

	// ���� : ����
	struct WEAPON
	{
		globalDigit PRESS		= 1 << 0x0;
		globalDigit RELOAD		= 1 << 0x1;
		
		globalDigit DO_FIRE		= 1 << 0x2;

		globalDigit NONE		= 0;
	};
};
