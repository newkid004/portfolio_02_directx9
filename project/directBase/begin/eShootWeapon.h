#pragma once
#include "kGlobalDefine.h"
#include "eventBase.h"

class particlePoint;

class eShootWeapon : public eventBase
{
private :
	particlePoint* _particle = nullptr;

public :
	void update(void) override;
	void draw(void) override;

private :
	particlePoint* createParticle(D3DXVECTOR3 & pos, D3DXVECTOR3 & normal);

public:
	eShootWeapon(void* sour, unsigned long paramType);
	~eShootWeapon();
};

