#pragma once

#include "weaponBase.h"

class weaponNormal :public weaponBase
{
public:
	virtual void updateWeapon(D3DXMATRIXA16 combineMatrix[], bool isCull) override;

protected:
	virtual void normalPre(void) override;
	virtual void normalDo(void) override;
	virtual void normalPost(void) override;

	virtual bool isNormalPossible(void) override;
public:
	weaponNormal(characterBase* linkPatternDup, int damage);
	virtual ~weaponNormal(void);
};