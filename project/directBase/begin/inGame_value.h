#pragma once
#include "kGlobalDefine.h"

#define defType constexpr static float

struct inGame_value
{
	struct global
	{
		defType gravity			= 3.0f;
		defType friction		= 2.25f;	// 초당 마찰력
	
		defType PI				= D3DX_PI;
		defType PIPI			= D3DX_PI * 2.0f;
		defType P2I				= D3DX_PI / 2.0f;
	};

	struct enemy
	{
		defType delayHangOut	= 4.0f;		// 서성거림		( 비탐색 상태 )
		defType delayAlert		= 0.5f;		// 경고 상태	( 탐색 활성화 )
		defType delayMove		= 0.05f;	// 이동 상태	( 짧은 탐색주기 )
		
		//defType delayAttack		= 1.25f;	// 공격 간격
	};
};