#pragma once

#define defType static constexpr int

struct inGame_digit
{
	struct KEY
	{
		defType W			= 1 << 0x0;
		defType S			= 1 << 0x1;
		defType A			= 1 << 0x2;
		defType D			= 1 << 0x3;
	};

	// ���� : ĳ����
	struct MOVE
	{
		defType MOVEING		= 1 << 0x0;
		defType LAND		= 1 << 0x1;
		defType FLOAT		= 1 << 0x2;

		defType NONE		= 0;
	};

	// ���� : ĳ����, AI
	struct CHAR
	{
		defType IDLE		= 1 << 0x0;		// �⺻ ����
		defType ALERT		= 1 << 0x1;		// ��� ����
		defType APPROACH	= 1 << 0x2;		// ���� ����
		defType ADJACENT	= 1 << 0x3;		// ���� ����
		defType ATTACK		= 1 << 0x4;		// ���� ����
		defType LROTATE		= 1 << 0x5;		// lȸ�� ����
		defType RROTATE		= 1 << 0x6;		// rȸ�� ����
		defType FALL		= 1 << 0x7;		// �������� ����
		defType BESHOT		= 1 << 0x8;		// �ǰ� ����
		defType SHOVED		= 1 << 0x9;		// ������ ���� 

		defType DEAD		= 1 << 0x1f;

		defType NONE		= 0;
	};

	struct ENEMY
	{
		defType COMMON		= 1 << 0x0;		// �Ϲ� ����
		defType TANK		= 1 << 0x1;		// ��ũ

		defType NONE		= 0;
	};

	// ���� : ����
	struct WEAPON
	{
		defType PRESS		= 1 << 0x0;
		defType RELOAD		= 1 << 0x1;
		
		defType DO_FIRE	= 1 << 0x2;

		defType NONE		= 0;
	};
};
