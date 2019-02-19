#pragma once

#include "bulletBase.h"

class fistBullet : public bulletBase
{
	
public:
	
	virtual void update(void) override;

public:

	void setRange(void);

	D3DXVECTOR3 & getDestOrigin(void) { return _destOrigin; }

public:

	fistBullet(float speed, EBulletType type = EBulletType::B_RIFLE);
	virtual ~fistBullet(void);
	
private:

	D3DXVECTOR3 _destOrigin;
};