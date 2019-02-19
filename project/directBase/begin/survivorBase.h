#pragma once
#include "kGlobalDefine.h"
#include "characterBase.h"

class weaponBase;

class survivorBase : public characterBase
{
protected :
	weaponBase* _weaponSub = nullptr;

public :
	weaponBase* & getWeaponSub(void) { return _weaponSub; }

public:
	survivorBase(patternMesh* duplicateTarget);
	~survivorBase();
};

