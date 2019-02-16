#pragma once
#include "kGlobalDefine.h"
#include "survivorBase.h"

class player : public survivorBase
{
public:
	player(const survivorBase::mParam param);
	~player();
};

