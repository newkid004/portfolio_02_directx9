#pragma once

struct inGame_digit
{
	// 적용 : 캐릭터
	struct MOVE
	{
		const static int MOVEING	= 1 << 0x0;
		const static int LAND		= 1 << 0x1;
		const static int FLOAT		= 1 << 0x2;

		const static int NONE		= 0;
	};

	// 적용 : 캐릭터, AI
	struct CHAR
	{
		const static int ALERT		= 1 << 0x0;		// 인식 여부
		const static int APPROACH	= 1 << 0x1;		// 접근 여부
		const static int ATTACK		= 1 << 0x2;		// 공격 여부

		const static int DEAD		= 1 << 0x1f;

		const static int NONE		= 0;
	};

	// 적용 : 무기
	struct WEAPON
	{
		const static int PRESS		= 1 << 0x0;
		const static int RELOAD		= 1 << 0x1;

		const static int NONE		= 0;
	};
};
