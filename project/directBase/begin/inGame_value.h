#pragma once
#include "kGlobalDefine.h"

struct inGame_value
{
private :
	#define defType constexpr static float

public :
	defType gravity		= 3.0f;
	defType friction	= 2.25f;	// 초당 마찰력
	
	defType PI			= D3DX_PI;
	defType PIPI		= D3DX_PI * 2.0f;
	defType P2I			= D3DX_PI / 2.0f;


};