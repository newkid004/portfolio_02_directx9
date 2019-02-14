#pragma once

struct inGame_digit
{
	// ���� : ĳ����
	struct MOVE
	{
		const static int MOVEING	= 1 << 0x0;
		const static int LAND		= 1 << 0x1;
		const static int FLOAT		= 1 << 0x2;

		const static int NONE		= 0;
	};

	// ���� : ĳ����, AI
	struct CHAR
	{
		const static int ALERT		= 1 << 0x0;		// �ν� ����
		const static int APPROACH	= 1 << 0x1;		// ���� ����
		const static int ATTACK		= 1 << 0x2;		// ���� ����

		const static int DEAD		= 1 << 0x1f;

		const static int NONE		= 0;
	};

	// ���� : ����
	struct WEAPON
	{
		const static int PRESS		= 1 << 0x0;
		const static int RELOAD		= 1 << 0x1;

		const static int NONE		= 0;
	};
};
