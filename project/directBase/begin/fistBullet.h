#pragma once

#include "bulletBase.h"

class weaponBase;

class fistBullet : public bulletBase
{
	
public:
	
	virtual void update(void) override;

public:

	void setRange(void);

	D3DXVECTOR3 & getDestOrigin(void) { return _destOrigin; }
	float & getTime(void) { return _fPlayTime; }

public:

	fistBullet(float speed, weaponBase* bind);
	virtual ~fistBullet(void);
	
private:

	D3DXVECTOR3 _destOrigin;
	float _fPlayTime = 5.0f;
};