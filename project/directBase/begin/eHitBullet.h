#pragma once
#include "kGlobalDefine.h"
#include "eventBase.h"

class bulletBase;
class weaponBase;
class characterBase;

class particlePoint;

class eHitCharacterBullet : public eventBase
{
protected :
	particlePoint* _particle = nullptr;

public :
	void update(void) override;
	void draw(void) override;

protected :
	void putDigitStatus(weaponBase* weapon, characterBase* take);
	void putValue(weaponBase* weapon, characterBase* take);

	particlePoint* createParticle(D3DXVECTOR3 & pos, D3DXVECTOR3 & normal);

public:
	eHitCharacterBullet(bulletBase* bullet, characterBase* take);
	~eHitCharacterBullet();
};

