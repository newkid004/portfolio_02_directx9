#pragma once
#include "kGlobalDefine.h"

struct inGame_value
{
private :
	#define defType constexpr static float

public :
	defType gravity		= 0.75f;
	defType friction	= 0.2f;	// �ʴ� ������
	
	defType PI			= D3DX_PI;
	defType PIPI		= D3DX_PI * 2.0f;
	defType P2I			= D3DX_PI / 2.0f;


};