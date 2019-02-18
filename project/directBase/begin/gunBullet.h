#pragma once

#include "bulletBase.h"

class gunBullet : public bulletBase
{

public:

	virtual void update(void) override;

public:

	gunBullet(float speed, EBulletType type = EBulletType::B_RIFLE);
	virtual ~gunBullet(void);

};