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

	// 적용 : 캐릭터
	struct MOVE
	{
		defType MOVEING		= 1 << 0x0;
		defType LAND		= 1 << 0x1;
		defType FLOAT		= 1 << 0x2;

		defType NONE		= 0;
	};

	// 적용 : 캐릭터, AI
	struct CHAR
	{
		defType IDLE		= 1 << 0x0;		// 기본 상태
		defType ALERT		= 1 << 0x1;		// 경계 상태
		defType APPROACH	= 1 << 0x2;		// 접근 여부
		defType ADJACENT	= 1 << 0x3;		// 인접 여부
		defType ATTACK		= 1 << 0x4;		// 공격 여부
		defType LROTATE		= 1 << 0x5;		// l회전 여부
		defType RROTATE		= 1 << 0x6;		// r회전 여부
		defType FALL		= 1 << 0x7;		// 떨어지는 상태
		defType BESHOT		= 1 << 0x8;		// 피격 상태
		defType SHOVED		= 1 << 0x9;		// 밀쳐진 상태 

		defType DEAD		= 1 << 0x1f;

		defType NONE		= 0;
	};

	struct ENEMY
	{
		defType COMMON		= 1 << 0x0;		// 일반 좀비
		defType TANK		= 1 << 0x1;		// 탱크

		defType NONE		= 0;
	};

	// 적용 : 무기
	struct WEAPON
	{
		defType PRESS		= 1 << 0x0;
		defType RELOAD		= 1 << 0x1;
		
		defType DO_FIRE	= 1 << 0x2;

		defType NONE		= 0;
	};
};
