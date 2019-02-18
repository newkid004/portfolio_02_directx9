#pragma once
#include "kGlobalDefine.h"

#include "inGame_struct.h"
#include "weaponBase.h"

class weaponShotgun :public weaponBase
{
protected:
	virtual void firePre(void) override;
	virtual void fireDo(void) override;
	virtual void firePost(void) override;

	virtual void reloadPre(void) override;
	virtual void reloadDo(void) override;
	virtual void reloadPost(void) override;

	virtual void updateHandMatrix(D3DXMATRIXA16 combineMatrix[]) override;
public:
	weaponShotgun(staticMesh::mParam param , characterBase* linkPatternDup, int damage);
	virtual ~weaponShotgun();
};