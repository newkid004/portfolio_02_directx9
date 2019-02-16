#pragma once
#include "kGlobalDefine.h"
#include "aStar_grape_bind.h"

class inGame_node;

class inGame_grape : public aStar_grape_bind<inGame_node>
{
public:
	inGame_grape() {};
	~inGame_grape() {};
};