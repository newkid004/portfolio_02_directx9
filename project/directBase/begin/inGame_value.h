#pragma once
#include "kGlobalDefine.h"

struct inGame_value
{
	struct global
	{
		globalReal gravity					= 3.0f;
		globalReal friction					= 2.25f;	// 초당 마찰력
	
		globalReal PI						= D3DX_PI;
		globalReal PIPI						= D3DX_PI * 2.0f;
		globalReal P2I						= D3DX_PI / 2.0f;
	};

	struct enemy
	{
		globalReal delayHangOut				= 4.0f;		// 서성거림		( 비탐색 상태 )
		globalReal delayAlert				= 0.5f;		// 경고 상태	( 탐색 활성화 )
		globalReal delayMove				= 0.05f;	// 이동 상태	( 짧은 탐색주기 )

		globalReal aletyDistance			= 80.0f;
		globalReal findSomthingDistance		= 70.0f;
		
		//globalReal delayAttack		= 1.25f;	// 공격 간격
	};

	struct bullet
	{
		globalReal speed					= 8.0f;
	};
};