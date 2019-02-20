#pragma once

#include "weaponBase.h"

class weaponNormal :public weaponBase
{
protected:
	virtual void firePre(void) override;
	virtual void fireDo(void) override;
	virtual void firePost(void) override;

	virtual void reloadPre(void) override;
	virtual void reloadDo(void) override;
	virtual void reloadPost(void) override;

	virtual void reloadBullet() {};
public:
	weaponNormal(characterBase* linkPatternDup, int damage);
	virtual ~weaponNormal(void);
};