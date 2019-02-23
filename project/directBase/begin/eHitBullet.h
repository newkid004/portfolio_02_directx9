#pragma once
#include "kGlobalDefine.h"
#include "eventBase.h"

class eHitBullet : public eventBase
{
public:
	eHitBullet(void* bullet, void* take, unsigned long param);
	~eHitBullet() {};
};

