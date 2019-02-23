#pragma once
#include "kGlobalDefine.h"
#include "eventBase.h"

class bulletBase;
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
	void putDigitStatus(bulletBase* bullet, characterBase* take, int hitPart);
	void putValue(bulletBase* bullet, characterBase* take);

	particlePoint* createParticle(D3DXVECTOR3 & pos, D3DXVECTOR3 & normal);

public:
	eHitCharacterBullet(bulletBase* bullet, characterBase* take, int hitPart);
	~eHitCharacterBullet();
};

