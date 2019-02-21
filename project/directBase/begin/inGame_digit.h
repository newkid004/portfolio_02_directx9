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

	// 적용 : 캐릭터
	struct MOVE
	{
		globalDigit MOVEING		= 1 << 0x0;
		globalDigit LAND		= 1 << 0x1;
		globalDigit FLOAT		= 1 << 0x2;

		globalDigit NONE		= 0;
	};

	// 적용 : 캐릭터, AI
	struct CHAR
	{
		globalDigit IDLE		= 1 << 0x0;		// 기본 상태
		globalDigit ALERT		= 1 << 0x1;		// 경계 상태
		globalDigit APPROACH	= 1 << 0x2;		// 접근 여부
		globalDigit ADJACENT	= 1 << 0x3;		// 인접 여부
		globalDigit ATTACK		= 1 << 0x4;		// 공격 여부
		globalDigit LROTATE		= 1 << 0x5;		// l회전 여부
		globalDigit RROTATE		= 1 << 0x6;		// r회전 여부
		globalDigit FALL		= 1 << 0x7;		// 떨어지는 상태
		globalDigit BESHOT		= 1 << 0x8;		// 피격 상태
		globalDigit SHOVED		= 1 << 0x9;		// 밀쳐진 상태 

		globalDigit DEAD		= 1 << 0x1f;

		globalDigit NONE		= 0;
	};

	struct ENEMY
	{
		globalDigit COMMON		= 1 << 0x0;		// 일반 좀비
		globalDigit TANK		= 1 << 0x1;		// 탱크

		globalDigit NONE		= 0;
	};

	// 적용 : 무기
	struct WEAPON
	{
		globalDigit PRESS		= 1 << 0x0;
		globalDigit RELOAD		= 1 << 0x1;
		
		globalDigit DO_FIRE		= 1 << 0x2;

		globalDigit NONE		= 0;
	};
};
