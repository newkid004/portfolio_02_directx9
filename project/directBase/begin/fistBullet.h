#pragma once

#include "bulletBase.h"

class fistBullet : public bulletBase
{
	
public:
	
	virtual void update(void) override;

public:

	fistBullet(float speed, EBulletType type = EBulletType::B_RIFLE);
	virtual ~fistBullet(void);
	
};