#pragma once

struct inGame_digit
{
	struct KEY
	{
		constexpr static int W			= 1 << 0x0;
		constexpr static int S			= 1 << 0x1;
		constexpr static int A			= 1 << 0x2;
		constexpr static int D			= 1 << 0x3;
	};

	// ���� : ĳ����
	struct MOVE
	{
		constexpr static int MOVEING	= 1 << 0x0;
		constexpr static int LAND		= 1 << 0x1;
		constexpr static int FLOAT		= 1 << 0x2;

		constexpr static int NONE		= 0;
	};

	// ���� : ĳ����, AI
	struct CHAR
	{
		constexpr static int IDLE		= 1 << 0x0;		// �⺻ ����
		constexpr static int ALERT		= 1 << 0x1;		// ��� ����
		constexpr static int APPROACH	= 1 << 0x2;		// ���� ����
		constexpr static int ADJACENT	= 1 << 0x3;		// ���� ����
		constexpr static int ATTACK		= 1 << 0x4;		// ���� ����
		constexpr static int LROTATE	= 1 << 0x5;		// lȸ�� ����
		constexpr static int RROTATE	= 1 << 0x6;		// rȸ�� ����
		constexpr static int FALL		= 1 << 0x7;		// �������� ����
		constexpr static int BESHOT		= 1 << 0x8;		// �ǰ� ����
		constexpr static int SHOVED		= 1 << 0x9;		// ������ ���� 

		constexpr static int DEAD		= 1 << 0x1f;

		constexpr static int NONE		= 0;
	};

	// ���� : ����
	struct WEAPON
	{
		constexpr static int PRESS		= 1 << 0x0;
		constexpr static int RELOAD		= 1 << 0x1;
		
		constexpr static int DO_FIRE	= 1 << 0x2;

		constexpr static int NONE		= 0;
	};
};
